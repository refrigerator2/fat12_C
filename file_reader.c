#include "file_reader.h"

int fat12_is_valid_data_cluster(uint16_t c) { return c >= 2 && c <= 0xFEF; }
struct file_t *file_open(struct volume_t *pvolume, const char *file_name) {
  if (!pvolume || !file_name) {
    errno = EFAULT;
    perror("file_open");
    return NULL;
  }
  struct file_t *file = calloc(1, sizeof(struct file_t));
  if (!file) {
    errno = ENOMEM;
    perror("file_open");
    return NULL;
  }
  for (int i = 0; i < pvolume->ss->root_entries; i++) {
    const char *ext = strchr(file_name, '.');
    if (ext != NULL && strlen(ext) - 1 > MAX_EXTENSION_LEN) {
      free(file);
      errno = EINVAL;
      perror("file_open");
      return NULL;
    }
    if ((ext != NULL &&
         strncmp(file_name, (pvolume->root_dir + i)->name,
                 strlen(file_name) - MAX_EXTENSION_LEN - 1) == 0 &&
         (strncmp(ext + 1, (pvolume->root_dir + i)->name + MAX_FILE_NAME_LEN,
                  strlen(ext) - 1) == 0)) ||
        strncmp(file_name, (pvolume->root_dir + i)->name, strlen(file_name)) ==
            0) {
      if ((pvolume->root_dir + i)->attrs & 0x10) {
        errno = EISDIR;
        perror("file_open");
        free(file);
        return NULL;
      }

      file->status = 1;
      file->first_cluster = (pvolume->root_dir + i)->young_word;
      file->current_cluster = (pvolume->root_dir + i)->young_word;
      file->offset = 0;
      file->size = (pvolume->root_dir + i)->size;
      file->vol = pvolume;
      return file;
    }
  }
  free(file);
  errno = ENOENT;
  perror("file_open");
  return NULL;
}
int file_close(struct file_t *stream) {
  if (!stream) {
    errno = EFAULT;
    perror("file_close");
    return -1;
  }
  stream->status = 0;
  free(stream);
  return 0;
}
uint16_t get_fat_entry(struct volume_t *vol, uint16_t cluster_id) {
  if (!vol) {
    errno = EFAULT;
    perror("get_fat_entry");
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
  if (!ptr || !stream || size == 0 || nmemb == 0 || !stream->vol ||
      !stream->vol->did) {
    errno = EFAULT;
    perror("file_read");
    return -1;
  }

  uint8_t *output = (uint8_t *)ptr;
  size_t total_to_read = size * nmemb;
  if (stream->offset >= stream->size) {
    return 0;
  }
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
      perror("file_read");
      break;
    }
    uint32_t remaining_in_sector =
        stream->vol->did->sector_size - byte_in_sector;
    uint32_t can_copy = total_to_read - bytes_read;

    if (can_copy > remaining_in_sector)
      can_copy = remaining_in_sector;

    memcpy(output + bytes_read, temp_buf + byte_in_sector, can_copy);

    bytes_read += can_copy;
    stream->offset += can_copy;

    if (stream->offset % cluster_size == 0) {
      uint16_t next = get_fat_entry(stream->vol, stream->current_cluster);
      if (next >= 0xFF8) {
        break;
      }
      if (!fat12_is_valid_data_cluster(next)) {
        errno = EIO;
        perror("file_read");
        return -1;
      }
      stream->current_cluster = next;
    }
  }

  return bytes_read / size;
}
int32_t file_seek(struct file_t *stream, int32_t offset, int whence) {
  if (!stream) {
    errno = EFAULT;
    perror("file_seek");
    return -1;
  }
  off_t new_offset = 0;
  switch (whence) {
  case SEEK_SET: {
    new_offset = offset;
    break;
  }
  case SEEK_CUR: {
    new_offset = stream->offset + offset;
    break;
  }
  case SEEK_END: {
    new_offset = stream->size + offset;
    break;
  }
  default: {
    errno = EINVAL;
    perror("file_seek");
    return -1;
  }
  }
  if (new_offset < 0 || new_offset >= (off_t)stream->size) {
    errno = ENXIO;
    perror("file_seek");
    return -1;
  }
  int number_of_clusters_to_skip =
      new_offset / (stream->vol->ss->bytes_per_sector *
                    stream->vol->ss->sectors_per_cluster);
  uint16_t first_cluster_clone = stream->first_cluster;
  for (int i = 0; i < number_of_clusters_to_skip; i++) {
    first_cluster_clone = get_fat_entry(stream->vol, first_cluster_clone);
  }
  stream->current_cluster = first_cluster_clone;
  stream->offset = new_offset;
  return new_offset;
}
struct volume_t *fat_open(struct disk_t *pdisk, uint32_t first_sector) {
  if (!pdisk) {
    errno = EFAULT;
    perror("fat_open");
    return NULL;
  }

  struct volume_t *vol = calloc(1, sizeof(struct volume_t));
  if (!vol) {
    errno = ENOMEM;
    perror("fat_open");
    return NULL;
  }

  vol->ss = malloc(sizeof(struct supersector));
  if (!vol->ss) {
    errno = ENOMEM;
    goto fail;
  }
  off_t lseek_res =
      lseek(pdisk->id, first_sector * pdisk->sector_size, SEEK_SET);
  if (lseek_res == -1)
    goto fail;

  ssize_t bytes = read(pdisk->id, vol->ss, sizeof(struct supersector));
  if (bytes != sizeof(struct supersector)) {
    if (bytes != -1)
      errno = ERANGE; /* the image is shorter than the boot sector */
    goto fail;
  }
  if (vol->ss->bytes_per_sector != pdisk->sector_size) {
    errno = EINVAL;
    goto fail;
  }

  uint32_t fat_size_bytes =
      vol->ss->sectors_per_fat * vol->ss->bytes_per_sector;
  vol->fat_table = malloc(fat_size_bytes);
  if (!vol->fat_table) {
    errno = ENOMEM;
    goto fail;
  }
  uint32_t fat_offset =
      (first_sector + vol->ss->reserved_sectors) * vol->ss->bytes_per_sector;
  if (lseek(pdisk->id, fat_offset, SEEK_SET) == -1)
    goto fail;
  bytes = read(pdisk->id, vol->fat_table, fat_size_bytes);
  if (bytes != (ssize_t)fat_size_bytes) {
    if (bytes != -1)
      errno = ERANGE;
    goto fail;
  }

  vol->did = pdisk;
  vol->fsector = first_sector;
  vol->fat_offset = fat_offset;
  vol->root_offset = vol->fat_offset + vol->ss->num_fats * fat_size_bytes;
  vol->root_dir = malloc(vol->ss->root_entries * sizeof(struct dir_entry_t));
  if (!vol->root_dir) {
    errno = ENOMEM;
    goto fail;
  }
  if (lseek(vol->did->id, vol->root_offset, SEEK_SET) == -1)
    goto fail;
  bytes = read(vol->did->id, vol->root_dir,
               vol->ss->root_entries * sizeof(struct dir_entry_t));
  if (bytes != (ssize_t)(vol->ss->root_entries * sizeof(struct dir_entry_t))) {
    if (bytes != -1)
      errno = ERANGE;
    goto fail;
  }
  int32_t data_offset_bytes =
      vol->root_offset + vol->ss->root_entries * sizeof(struct dir_entry_t);
  vol->data_offset_sectors =
      data_offset_bytes / vol->ss->bytes_per_sector - first_sector;
  return vol;

fail:
  perror("fat_open");
  free(vol->root_dir);
  free(vol->fat_table);
  free(vol->ss);
  free(vol);
  return NULL;
}
int fat_close(struct volume_t *pvolume) {
  if (!pvolume) {
    errno = EFAULT;
    perror("fat_close");
    return -1;
  }
  free(pvolume->fat_table);
  free(pvolume->ss);
  free(pvolume->root_dir);
  free(pvolume);
  return 0;
}
struct disk_t *disk_open_from_file(const char *volume_file_name) {
  if (!volume_file_name) {
    errno = EFAULT;
    perror("disk_open_from_file");
    return NULL;
  }
  int fd = open(volume_file_name, O_RDONLY);
  if (fd == -1) {
    errno = ENOENT;
    perror("disk_open_from_file");
    return NULL;
  }
  struct disk_t *disk = calloc(1, sizeof(struct disk_t));
  if (!disk) {
    close(fd);
    errno = ENOMEM;
    perror("disk_open_from_file");
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
    perror("disk_read");
    return -1;
  }
  int counter = 0;
  off_t res = lseek(pdisk->id, first_sector * pdisk->sector_size, SEEK_SET);
  if (res == -1) {
    errno = ERANGE;
    perror("disk_read");
    return -1;
  }
  for (int i = 0; i < sectors_to_read; i++) {
    int bytes_read =
        read(pdisk->id, (uint8_t *)buffer + counter, pdisk->sector_size);
    if (bytes_read != pdisk->sector_size) {
      errno = ERANGE;
      perror("disk_read");
      return -1;
    }
    counter += bytes_read;
  }
  return sectors_to_read;
}
int disk_close(struct disk_t *pdisk) {
  if (!pdisk) {
    errno = EFAULT;
    perror("disk_close");
    return -1;
  }
  close(pdisk->id);
  free(pdisk);
  return 0;
}
struct dir_t *dir_open(struct volume_t *pvolume, const char *dir_path) {
  if (!pvolume || !dir_path) {
    errno = EFAULT;
    perror("dir_open");
    return NULL;
  }
  struct dir_t *dir = calloc(1, sizeof(struct dir_t));
  if (!dir) {
    errno = ENOMEM;
    perror("dir_open");
    return NULL;
  }
  if (strcmp(dir_path, "\\") == 0) {
    dir->vol = pvolume;
    dir->offset = 0;
    dir->first_cluster = 0;
    dir->current_cluster = 0;
    return dir;
  }
  for (int i = 0; i < pvolume->ss->root_entries; i++) {

    if (strncmp(dir_path, (pvolume->root_dir + i)->name, strlen(dir_path)) ==
        0) {
      if (!((pvolume->root_dir + i)->attrs & 0x10)) {
        errno = ENOTDIR;
        perror("dir_open");
        free(dir);
        return NULL;
      }
      dir->current_cluster = (pvolume->root_dir + i)->young_word;
      dir->first_cluster = (pvolume->root_dir + i)->young_word;
      dir->offset = 0;
      dir->vol = pvolume;
      dir->size = pvolume->ss->root_entries;
      return dir;
    }
  }
  errno = ENOENT;
  perror("dir_open");
  free(dir);
  return NULL;
}
int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry) {
  if (!pdir || !pentry || !pdir->vol) {
    errno = EFAULT;
    perror("dir_read");
    return -1;
  }

  /* Root directory: all entries are already in memory */
  if (pdir->first_cluster == 0) {
    while (pdir->offset < pdir->vol->ss->root_entries) {
      struct dir_entry_t *entry = pdir->vol->root_dir + pdir->offset;
      uint8_t first_byte = (uint8_t)entry->name[0];
      if (first_byte == 0x00)
        return 1; /* no more entries */
      pdir->offset++;
      if (first_byte == 0xE5 || entry->attrs == 0x0F || (entry->attrs & 0x08))
        continue; /* deleted entry, long file name or volume label */
      *pentry = *entry;
      return 0;
    }
    return 1;
  }

  /* Subdirectory: its entries are stored in the clusters of the data area */
  uint32_t sector_size = pdir->vol->did->sector_size;
  uint32_t cluster_size = pdir->vol->ss->sectors_per_cluster * sector_size;
  uint8_t temp_buf[512];

  while (pdir->current_cluster < 0xFF8) {
    uint32_t offset_in_cluster =
        (pdir->offset * sizeof(struct dir_entry_t)) % cluster_size;
    uint32_t lba =
        pdir->vol->fsector + pdir->vol->data_offset_sectors +
        (pdir->current_cluster - 2) * pdir->vol->ss->sectors_per_cluster +
        offset_in_cluster / sector_size;
    if (disk_read(pdir->vol->did, lba, temp_buf, 1) != 1) {
      perror("dir_read");
      return -1;
    }
    memcpy(pentry, temp_buf + offset_in_cluster % sector_size,
           sizeof(struct dir_entry_t));

    uint8_t first_byte = (uint8_t)pentry->name[0];
    if (first_byte == 0x00)
      return 1; /* no more entries */
    pdir->offset++;

    if ((pdir->offset * sizeof(struct dir_entry_t)) % cluster_size == 0) {
      pdir->current_cluster = get_fat_entry(pdir->vol, pdir->current_cluster);
      if (pdir->current_cluster < 0xFF8 &&
          !fat12_is_valid_data_cluster(pdir->current_cluster)) {
        errno = EIO;
        perror("dir_read");
        return -1;
      }
    }
    if (first_byte == 0xE5 || pentry->attrs == 0x0F || (pentry->attrs & 0x08))
      continue;
    return 0;
  }
  return 1; /* end of the cluster chain */
}
int dir_close(struct dir_t *pdir) {
  if (!pdir) {
    errno = EFAULT;
    perror("dir_close");
    return -1;
  }
  free(pdir);
  return 0;
}
