

#include "file_reader.h"
#include "rdebug.h"
#include "tested_declarations.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

struct file_t *file_open(struct volume_t *pvolume, const char *file_name) {
  if (!pvolume || !file_name) {
    errno = EFAULT;
    perror("baza");
    return NULL;
  }
  struct file_t *file = calloc(1, sizeof(struct file_t));
  if (!file) {
    errno = ENOMEM;
    perror("memory");
    return NULL;
  }
  for (int i = 0; i < pvolume->ss->root_dir_entries; i++) {
    if (strncmp(file_name, (pvolume->root_dir + i)->name, strlen(file_name)) ==
        0) {
      if ((pvolume->root_dir + i)->attrs & 16)
        printf("ajajaj\n");
      printf("%s\n", (pvolume->root_dir + i)->name);

      file->status = 1;
      file->first_cluster = (pvolume->root_dir + i)->first_cluster;
      file->current_cluster = (pvolume->root_dir + i)->first_cluster;
      file->offset = 0;
      file->size = (pvolume->root_dir + i)->first_cluster;
      file->fat_table = malloc(sizeof(uint8_t) * pvolume->ss->fat_count);
      if (!file->fat_table) {
        errno = ENOMEM;
        perror("memory");
        return NULL;
      }
      memcpy(file->fat_table, pvolume->fat_table,
             sizeof(uint8_t) * pvolume->ss->fat_count);
      file->vol = pvolume;
      return file;
    }
  }
  errno = ENOENT;
  perror("no such file");
  return NULL;
}
int file_close(struct file_t *stream) { return 0; }
uint16_t get_fat_entry(struct volume_t *vol, uint16_t cluster_id) {
  if (!vol) {
    printf("Mozet byt nuzen errno");
    return 0;
  }
  uint32_t offset = (cluster_id * 3) / 2;
  uint16_t val = *(uint16_t *)(vol->fat_table + offset);

  if (cluster_id % 2 == 0) {
    return val & 0x0FFF;
  } else {
    return val >> 4;
  }
}

size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream) {
  if (!ptr || !stream || size == 0 || nmemb == 0) {
    errno = EFAULT;
    return 0;
  }

  uint8_t *output = (uint8_t *)ptr;
  size_t total_to_read = size * nmemb;
  if (stream->offset + total_to_read > stream->size) {
    total_to_read = stream->size - stream->offset;
  }

  size_t bytes_read = 0;
  uint8_t temp_buf[512];

  while (bytes_read < total_to_read) {
    uint32_t cluster_size =
        stream->vol->ss->sectors_per_cluster * stream->vol->did->sector_size;
    uint32_t offset_in_cluster = stream->offset % cluster_size;
    uint32_t sector_in_cluster =
        offset_in_cluster / stream->vol->did->sector_size;
    uint32_t byte_in_sector = offset_in_cluster % stream->vol->did->sector_size;

    uint32_t lba =
        stream->vol->fsector + stream->vol->data_offset_sectors +
        (stream->current_cluster - 2) * stream->vol->ss->sectors_per_cluster +
        sector_in_cluster;

    if (disk_read(stream->vol->did, lba, temp_buf, 1) != 1) {
      printf("dis_read went wronh\n");
      break;
    }
    printf("%s\n", (char *)temp_buf);
    uint32_t remaining_in_sector =
        stream->vol->did->sector_size - byte_in_sector;
    uint32_t can_copy = total_to_read - bytes_read;
    if (can_copy > remaining_in_sector)
      can_copy = remaining_in_sector;

    memcpy(output + bytes_read, temp_buf + byte_in_sector, can_copy);

    bytes_read += can_copy;
    stream->offset += can_copy;

    if (stream->offset % cluster_size == 0) {
      stream->current_cluster =
          get_fat_entry(stream->vol, stream->current_cluster);
      if (stream->current_cluster >= 0xFF8) {
        printf("0xff8\n");
        break;
      }
    }
  }

  return bytes_read / size;
}
int32_t file_seek(struct file_t *stream, int32_t offset, int whence) {

  return 0;
}
struct volume_t *fat_open(struct disk_t *pdisk, uint32_t first_sector) {
  if (!pdisk) {
    errno = EFAULT;
    return NULL;
  }

  struct volume_t *vol = calloc(1, sizeof(struct volume_t));
  if (!vol) {
    errno = ENOMEM;
    return NULL;
  }

  vol->ss = malloc(sizeof(struct supersector));
  if (!vol->ss) {
    free(vol);
    errno = ENOMEM;
    return NULL;
  }
  off_t lseek_res =
      lseek(pdisk->id, first_sector * pdisk->sector_size, SEEK_SET);

  if (lseek_res == -1 || read(pdisk->id, vol->ss, sizeof(struct supersector)) !=
                             sizeof(struct supersector)) {
    free(vol->ss);
    free(vol);
    printf("Jesli proizoshlo dobav errno");
    return NULL;
  }
  printf("ss: %d\n", vol->ss->total_sectors_16);
  if (vol->ss->bytes_per_sector != pdisk->sector_size) {
    free(vol->ss);
    free(vol);
    errno = EINVAL;
    return NULL;
  }

  uint32_t fat_size_bytes = vol->ss->fat_size_16 * vol->ss->bytes_per_sector;
  vol->fat_table = malloc(fat_size_bytes);
  if (!vol->fat_table) {
    free(vol->ss);
    free(vol);
    errno = ENOMEM;
    return NULL;
  }
  uint32_t fat_offset =
      (first_sector + vol->ss->reserved_sectors) * vol->ss->bytes_per_sector;
  off_t temp = lseek(pdisk->id, fat_offset, SEEK_SET);
  if (temp == -1) {
    printf("Smt went wrong\n");
  }
  long long int res = read(pdisk->id, vol->fat_table, fat_size_bytes);
  if (res == -1) {
    printf("SMT went wrong 2\n");
  }

  vol->did = pdisk;
  vol->fsector = first_sector;
  vol->fat_offset = fat_offset;
  vol->root_offset =
      vol->fat_offset +
      ((vol->ss->fat_size_16 * vol->ss->bytes_per_sector) * vol->ss->fat_count);
  vol->root_dir = malloc(vol->ss->root_dir_entries * 32);
  if (!vol->root_dir) {
    errno = ENOMEM;
    printf("malloc ne srabotal, w padlu chistku pisat bylo");
    return NULL;
  }
  lseek(vol->did->id, vol->root_offset, SEEK_SET);
  read(vol->did->id, vol->root_dir, vol->ss->root_dir_entries * 32);
  int32_t data_offset_bytes = vol->root_offset + vol->ss->root_dir_entries * 32;
  vol->data_offset_sectors =
      data_offset_bytes / vol->ss->bytes_per_sector - first_sector;
  pdisk->sector_size = vol->ss->bytes_per_sector;
  printf("\n%d %d \n", first_sector, vol->data_offset_sectors);
  return vol;
}
int fat_close(struct volume_t *pvolume) { return 0; }
struct disk_t *disk_open_from_file(const char *volume_file_name) {
  if (!volume_file_name) {
    errno = EFAULT;
    perror("open");
    return NULL;
  }
  int fd = open(volume_file_name, O_RDONLY);
  if (fd == -1) {
    errno = ENOENT;
    perror("open");
    return NULL;
  }
  struct disk_t *disk = calloc(1, sizeof(struct disk_t));
  if (!disk) {
    errno = ENOMEM;
    perror("memory");
    return NULL;
  }
  disk->id = fd;
  disk->sector_size = 512;
  return disk;
}
int disk_read(struct disk_t *pdisk, int32_t first_sector, void *buffer,
              int32_t sectors_to_read) {
  if (!pdisk || !buffer || first_sector < 0 || sectors_to_read < 0) {
    errno = EFAULT;
    return -1;
  }
  printf("%d %d %d %d\n", pdisk->id, first_sector, (int)sizeof(buffer),
         sectors_to_read);
  int counter = 0;
  off_t res = lseek(pdisk->id, first_sector * pdisk->sector_size, SEEK_SET);
  if (res == -1) {
    errno = ERANGE;
    printf("b\n");
    return -1;
  }
  for (int i = 0; i < sectors_to_read; i++) {
    int bytes_read =
        read(pdisk->id, (uint8_t *)buffer + counter, pdisk->sector_size);
    if (bytes_read != pdisk->sector_size) {
      errno = ERANGE;
      return -1;
    }
    counter += bytes_read;
  }
  return sectors_to_read;
}
int disk_close(struct disk_t *pdisk) {
  if (!pdisk) {
    errno = EFAULT;
    perror("variable");
    return -1;
  }
  close(pdisk->id);
  free(pdisk);
  return 0;
}
struct dir_t *dir_open(struct volume_t *pvolume, const char *dir_path) {

  return NULL;
}
int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry) { return 0; }
int dir_close(struct dir_t *pdir) { return 0; }
