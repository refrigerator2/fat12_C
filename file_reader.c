

#include "file_reader.h"
#include "rdebug.h"
#include "tested_declarations.h"

struct file_t *file_open(struct volume_t *pvolume, const char *file_name) {
  if (!pvolume || !file_name) {
    errno = EFAULT;
    return NULL;
  }
  uint64_t fat1_start = pvolume->volume_start + pvolume->reserved_sectors;
  uint64_t root_start =
      fat1_start + pvolume->fat_count * pvolume->sectors_per_fat;
  uint64_t sectors_per_root =
      pvolume->root_dir_capacity * sizeof(struct dir_entry_t) / SECTOR_SIZE;
  for (uint64_t i = 0; i < sectors_per_root; i++) {
    uint8_t *buf = malloc(SECTOR_SIZE * sizeof(uint8_t));
    if (!buf) {
      errno = ENOMEM;
      return NULL;
    }
    disk_read(pvolume->pdisk, root_start, buf, 1);
    for (uint32_t j = 0; j < SECTOR_SIZE; j += INFO_SIZE) {
      if (strncmp(file_name, (const char *)(buf + j), strlen(file_name)) == 0) {
        if (*(buf + j + 11) == 0x10 || *(buf + j + 11) == 0x08) {
          errno = EISDIR;
          free(buf);
          return NULL;
        }
        struct file_t *file = malloc(sizeof(struct file_t));
        if (!file) {
          errno = ENOMEM;
          free(buf);
          return NULL;
        }
        strncpy(file->name, (const char *)(buf + j), NAME_SIZE);
        strncpy(file->extension, (const char *)(buf + j + NAME_SIZE), EXT_SIZE);
        file->create_time = *(uint16_t *)(buf + j + CREATE_TIME_OFFSET);
        file->create_date = *(uint16_t *)(buf + j + CREATE_DATE_OFFSET);
        file->last_access_date = *(uint16_t *)(buf + j + LAST_ACCESS_DATE);
        file->last_mod_time = *(uint16_t *)(buf + j + LAST_MOD_TIME);
        file->last_mod_date = *(uint16_t *)(buf + j + LAST_MOD_DATE);
        file->first_claster_adr = *(uint16_t *)(buf + j + FIRST_CLASTER_OFFSET);
        file->size = *(uint32_t *)(buf + j + FILE_SIZE_OFFSET);
        file->cursor = 0;
        file->vol = pvolume;
        free(buf);
        return file;
      }
    }
    free(buf);
  }
  errno = ENOENT;
  return NULL;
}
int file_close(struct file_t *stream) {
  if (!stream) {
    errno = EFAULT;
    return -1;
  }
  free(stream);
  return 0;
}
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream) {
  if (!stream || !ptr) {
    errno = EFAULT;
    return -1;
  }
  while (1) {
  }
  return 0;
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

  return NULL;
}
int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry) { return 0; }
int dir_close(struct dir_t *pdir) { return 0; }
