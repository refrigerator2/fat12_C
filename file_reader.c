

#include "file_reader.h"
#include "rdebug.h"
#include "tested_declarations.h"
#include <ctype.h>
#include <stdint.h>
#include <string.h>

int open_helper(struct volume_t *pvolume, const char *file_name, uint8_t *info,
                uint8_t is_file) {
  if (!pvolume || !file_name) {
    errno = EFAULT;
    return 1;
  }
  char fat_name[NAME_SIZE + EXT_SIZE];
  memset(fat_name, ' ', NAME_SIZE + EXT_SIZE);
  int i = 0;
  for (; file_name[i] != '.' && !isspace(file_name[i]); i++) {
    if (i < NAME_SIZE) {
      fat_name[i] = toupper(file_name[i]);
    }
  }
  if (file_name[i] == '.') {
    int ext_idx = 0;
    i++;
    while (file_name[i] != '\0' && ext_idx < EXT_SIZE) {
      fat_name[NAME_SIZE + ext_idx] = toupper(file_name[i]);
      ext_idx++;
      i++;
    }
  }
  uint64_t fat1_start = pvolume->volume_start + pvolume->reserved_sectors;
  uint64_t root_start =
      fat1_start + pvolume->fat_count * pvolume->sectors_per_fat;
  uint64_t sectors_per_root =
      pvolume->root_dir_capacity * INFO_SIZE / SECTOR_SIZE;
  for (uint64_t i = 0; i < sectors_per_root; i++) {
    uint8_t buf[SECTOR_SIZE];
    disk_read(pvolume->pdisk, root_start + i, buf, 1);
    for (uint32_t j = 0; j < SECTOR_SIZE; j += INFO_SIZE) {
      if (buf[j] == 0x00 || buf[j] == 0xE5)
        continue;
      uint8_t attr = buf[j + ATTR_OFFSET];
      uint8_t is_dir_entry = (attr & 0x10) ? 0 : 1;
      if (is_dir_entry != is_file)
        continue;
      if (memcmp(buf + j, fat_name, NAME_SIZE + EXT_SIZE) == 0) {
        memcpy(info, buf + j, INFO_SIZE);
        return 0;
      }
    }
  }
  errno = ENOENT;
  return 1;
}

struct file_t *file_open(struct volume_t *pvolume, const char *file_name) {
  if (!pvolume || !file_name) {
    errno = EFAULT;
    return NULL;
  }

  uint8_t entry_buf[INFO_SIZE];

  if (open_helper(pvolume, file_name, entry_buf, 1) != 0) {
    return NULL;
  }

  uint8_t attr = entry_buf[ATTR_OFFSET];
  if ((attr & 0x10) || (attr & 0x08)) {
    errno = EISDIR;
    return NULL;
  }

  struct file_t *file = malloc(sizeof(struct file_t));
  if (!file) {
    errno = ENOMEM;
    return NULL;
  }

  strncpy(file->name, (const char *)entry_buf, NAME_SIZE);
  strncpy(file->extension, (const char *)(entry_buf + NAME_SIZE), EXT_SIZE);

  file->create_time = *(uint16_t *)(entry_buf + CREATE_TIME_OFFSET);
  file->create_date = *(uint16_t *)(entry_buf + CREATE_DATE_OFFSET);
  file->last_access_date = *(uint16_t *)(entry_buf + LAST_ACCESS_DATE);
  file->last_mod_time = *(uint16_t *)(entry_buf + LAST_MOD_TIME);
  file->last_mod_date = *(uint16_t *)(entry_buf + LAST_MOD_DATE);

  file->first_claster_adr = *(uint16_t *)(entry_buf + FIRST_CLASTER_OFFSET);
  file->size = *(uint32_t *)(entry_buf + FILE_SIZE_OFFSET);

  file->cursor = 0;
  file->vol = pvolume;

  return file;
}
int file_close(struct file_t *stream) {
  if (!stream) {
    errno = EFAULT;
    return -1;
  }
  free(stream);
  return 0;
}
uint16_t find_fat_id(const struct volume_t *vol, uint16_t prev_id) {
  if (!vol)
    return prev_id;
  uint32_t bytes_offset_in_fat = prev_id * 1.5;
  uint32_t sector_id =
      vol->volume_start + vol->reserved_sectors + (bytes_offset_in_fat / 512);

  uint8_t buffer[SECTOR_SIZE * 2];
  if (disk_read(vol->pdisk, sector_id, buffer, 2) == -1) {
    return prev_id;
  }
  uint32_t offset_in_sector = (bytes_offset_in_fat) % 512;
  uint16_t new_id = *(uint16_t *)(buffer + offset_in_sector);
  return new_id % 2 == 0 ? new_id & 0x0FFF : new_id >> 4;
}
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream) {
  if (!stream || !ptr) {
    errno = EFAULT;
    return -1;
  }
  uint32_t fat1_start =
      stream->vol->volume_start + stream->vol->reserved_sectors;
  uint32_t sectors_per_root = stream->vol->root_dir_capacity *
                              sizeof(struct dir_entry_t) /
                              stream->vol->bytes_per_sector;
  uint32_t data_start_sector =
      fat1_start + stream->vol->fat_count * stream->vol->sectors_per_fat +
      sectors_per_root;
  uint16_t fat_id = stream->first_claster_adr;
  size_t bytes_needed = size * nmemb;
  size_t byte_counter = 0;
  size_t ptr_pos = 0;
  uint32_t offset_in_file = stream->cursor;
  while (1) {
    uint32_t cluster_start =
        data_start_sector + (fat_id - 2) * stream->vol->sectors_per_cluster;

    int res;
    uint8_t buf[SECTOR_SIZE * stream->vol->sectors_per_cluster];
    if ((res = disk_read(stream->vol->pdisk, cluster_start, buf,
                         stream->vol->sectors_per_cluster)) == -1) {
      return -1;
    }
    if ((uint32_t)res * SECTOR_SIZE < offset_in_file) {
      offset_in_file -= (uint32_t)res * SECTOR_SIZE;
    } else {
      if (offset_in_file != 0) {
        memcpy(buf, buf + offset_in_file,
               (uint32_t)res * SECTOR_SIZE - offset_in_file);
        byte_counter += (size_t)res * SECTOR_SIZE - offset_in_file;
        offset_in_file = 0;
      } else {
        byte_counter += (size_t)res * SECTOR_SIZE;
      }
      if (bytes_needed <= byte_counter) {
        memcpy(ptr + ptr_pos, buf, bytes_needed - ptr_pos);
        return bytes_needed;
      }
      memcpy(ptr + ptr_pos, buf, (size_t)res * SECTOR_SIZE);
      ptr_pos += (size_t)res * SECTOR_SIZE;
      uint16_t temp = find_fat_id(stream->vol, fat_id);
      if (temp == fat_id) {
        return -1;
      }
      fat_id = temp;
      if (fat_id >= 0x0FF8) {
        break;
      }
    }
  }
  return byte_counter;
}
int32_t file_seek(struct file_t *stream, int32_t offset, int whence) {
  if (!stream) {
    errno = EFAULT;
    return -1;
  }
  int32_t parsed_whence;
  switch (whence) {
  case SEEK_CUR:
    parsed_whence = stream->cursor;
    break;
  case SEEK_SET:
    parsed_whence = 0;
    break;
  case SEEK_END:
    parsed_whence = stream->size;
    break;
  default:
    errno = EINVAL;
    return -1;
  }
  int64_t target_offset = parsed_whence + offset;

  if (target_offset > (int64_t)stream->size || target_offset < 0) {
    errno = ENXIO;
    return -1;
  }
  stream->cursor = (uint32_t)target_offset;
  return stream->cursor;
}
struct volume_t *fat_open(struct disk_t *pdisk, uint32_t first_sector) {
  if (!pdisk) {
    errno = EFAULT;
    return NULL;
  }
  struct volume_t *vol = malloc(sizeof(struct volume_t));
  if (!vol) {
    errno = ENOMEM;
    return NULL;
  }
  vol->pdisk = pdisk;
  lseek(pdisk->fd, first_sector * SECTOR_SIZE, SEEK_SET);
  lseek(pdisk->fd, 0x0B, SEEK_CUR);
  read(pdisk->fd, (uint8_t *)vol + sizeof(struct disk_t *), 0x15 - 0x0B);
  read(pdisk->fd, &vol->logical_sectors32, sizeof(vol->logical_sectors32));

  uint8_t sectors_per_cluster_possible[] = {1, 2, 4, 8, 16, 32, 64, 128};
  int was_in = 0;
  for (uint8_t i = 0; i < vol->sectors_per_cluster; i++) {
    if (sectors_per_cluster_possible[i] == vol->sectors_per_cluster) {
      was_in = 1;
      break;
    }
  }
  if (!was_in || (vol->fat_count != 1 && vol->fat_count != 2)) {
    errno = EINVAL;
    free(vol);
    return NULL;
  }
  if (!(vol->logical_sectors32 == 0 ^ vol->logical_sectors16 == 0)) {
    errno = EINVAL;
    free(vol);
    return NULL;
  }
  if (vol->logical_sectors16 != 0 && vol->logical_sectors32 > 65535) {
    errno = EINVAL;
    free(vol);
    return NULL;
  }
  if (!(vol->root_dir_capacity * sizeof(struct dir_entry_t) %
            vol->bytes_per_sector ==
        0)) {
    errno = EINVAL;
    free(vol);
    return NULL;
  }
  vol->volume_start = first_sector;
  return vol;
}
int fat_close(struct volume_t *pvolume) {
  if (!pvolume) {
    errno = EFAULT;
    return -1;
  }
  free(pvolume);
  return 0;
}

struct disk_t *disk_open_from_file(const char *volume_file_name) {
  if (!volume_file_name) {
    errno = EFAULT;
    return NULL;
  }
  int f = open(volume_file_name, O_RDONLY);
  if (!f) {
    errno = ENOENT;
    return NULL;
  }
  struct disk_t *disk = malloc(sizeof(struct disk_t));
  if (!disk) {
    close(f);
    errno = ENOMEM;
    return NULL;
  }
  disk->fd = f;

  return disk;
}
int disk_read(struct disk_t *pdisk, int32_t first_sector, void *buffer,
              int32_t sectors_to_read) {
  if (!pdisk || !buffer || sectors_to_read <= 0 || first_sector < 0) {
    errno = EFAULT;
    return -1;
  }

  uint64_t offset = first_sector * SECTOR_SIZE;
  if (lseek(pdisk->fd, offset, SEEK_SET) == -1) {
    errno = ERANGE;
    return -1;
  }

  size_t total_bytes_to_read = (size_t)sectors_to_read * SECTOR_SIZE;
  size_t bytes_read = read(pdisk->fd, buffer, total_bytes_to_read);

  if (bytes_read != total_bytes_to_read) {
    errno = ERANGE;
    return -1;
  }

  return sectors_to_read;
}
int disk_close(struct disk_t *pdisk) {
  if (!pdisk) {
    errno = EFAULT;
    return -1;
  }
  close(pdisk->fd);
  free(pdisk);
  return 0;
}
struct dir_t *dir_open(struct volume_t *pvolume, const char *dir_path) {
  if (!pvolume || !dir_path) {
    errno = EFAULT;
    return NULL;
  }

  uint8_t entry_buf[INFO_SIZE];

  if (open_helper(pvolume, dir_path, entry_buf, 1) != 0) {
    return NULL;
  }

  uint8_t attr = entry_buf[ATTR_OFFSET];
  if ((attr & 0x10) || (attr & 0x08)) {
    errno = EISDIR;
    return NULL;
  }

  struct dir_t *dir = malloc(sizeof(struct file_t));
  if (!dir) {
    errno = ENOMEM;
    return NULL;
  }

  strncpy(dir->name, (const char *)entry_buf, NAME_SIZE);

  dir->create_time = *(uint16_t *)(entry_buf + CREATE_TIME_OFFSET);
  dir->create_date = *(uint16_t *)(entry_buf + CREATE_DATE_OFFSET);
  dir->last_access_date = *(uint16_t *)(entry_buf + LAST_ACCESS_DATE);
  dir->last_mod_time = *(uint16_t *)(entry_buf + LAST_MOD_TIME);
  dir->last_mod_date = *(uint16_t *)(entry_buf + LAST_MOD_DATE);

  dir->first_claster_adr = *(uint16_t *)(entry_buf + FIRST_CLASTER_OFFSET);
  dir->size = *(uint32_t *)(entry_buf + FILE_SIZE_OFFSET);

  dir->vol = pvolume;

  return dir;
}
int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry) { return 0; }
int dir_close(struct dir_t *pdir) { return 0; }
