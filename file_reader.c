

#include "file_reader.h"
#include "rdebug.h"
#include "tested_declarations.h"
#include <asm-generic/errno-base.h>
#include <stdio.h>

struct file_t *file_open(struct volume_t *pvolume, const char *file_name) {

  return NULL;
}
int file_close(struct file_t *stream) { return 0; }
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream) {

  return 0;
}
int32_t file_seek(struct file_t *stream, int32_t offset, int whence) {

  return 0;
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
  lseek(pdisk->fd, 0x16 - 0x0B, SEEK_CUR);
  read(pdisk->fd, &vol->logical_sectors32, sizeof(vol->logical_sectors32));

  uint8_t sectors_per_cluster_possible[] = {1, 2, 4, 8, 16, 32, 64, 128};
  int was_in = 0;
  for (uint8_t i = 0; i < vol->sectors_per_cluster; i++) {
    if (sectors_per_cluster_possible[i] == vol->sectors_per_cluster) {
      was_in = 1;
      break;
    }
  }
  if (!was_in || vol->reserved_sectors < 0 ||
      (vol->fat_count != 1 && vol->fat_count != 2)) {
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
  if (!pdisk || !buffer) {
    errno = EFAULT;
    return -1;
  }
  if (lseek(pdisk->fd, first_sector * SECTOR_SIZE, SEEK_SET) == -1) {
    errno = ERANGE;
    return -1;
  }
  int32_t i;
  for (i = 0; i < sectors_to_read; i++) {
    if (lseek(pdisk->fd, i * SECTOR_SIZE, SEEK_CUR) == -1) {
      errno = ERANGE;
      return -1;
    }
    size_t bytes_read =
        read(pdisk->fd, (uint8_t *)buffer + (i * SECTOR_SIZE), SECTOR_SIZE);
    if (bytes_read != SECTOR_SIZE) {
      errno = ERANGE;
      return -1;
    }
  }
  return i + 1;
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
