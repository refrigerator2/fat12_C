#ifndef FILE_READER_H
#define FILE_READER_H
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct volume_t {
  struct disk_t *did;
  uint32_t fsector;
  struct supersector *ss;
  struct fat_dir_entry_t *root_dir;
  uint8_t *fat_table;
  uint32_t root_offset;
  uint32_t fat_offset;
  uint32_t data_offset_sectors;
};
struct file_t {
  uint8_t status;
  uint16_t first_cluster;
  uint32_t size;
  uint8_t *fat_table;
  struct volume_t *vol;
  uint16_t current_cluster;
  uint32_t offset;
};
struct disk_t {
  int id;
  uint16_t sector_size;
};
struct dir_t;

struct dir_entry_t {
  char *name;
  size_t size;
  uint8_t is_archived;
  uint8_t is_readonly;
  uint8_t is_system;
  uint8_t is_headden;
  uint8_t is_directory;
};
struct supersector {
  uint8_t jmp[3];
  char oem_name[8];
  uint16_t bytes_per_sector;
  uint8_t sectors_per_cluster;
  uint16_t reserved_sectors;
  uint8_t fat_count;
  uint16_t root_dir_entries;
  uint16_t total_sectors_16;
  uint8_t media_type;
  uint16_t fat_size_16;
} __attribute__((packed));

struct fat_dir_entry_t {
  char name[8];
  char ext[3];
  uint8_t attrs;
  uint8_t shit[14];
  uint16_t first_cluster;
  uint32_t size;
} __attribute__((packed));

struct file_t *file_open(struct volume_t *pvolume, const char *file_name);
int file_close(struct file_t *stream);
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream);
int32_t file_seek(struct file_t *stream, int32_t offset, int whence);

struct disk_t *disk_open_from_file(const char *volume_file_name);
int disk_read(struct disk_t *pdisk, int32_t first_sector, void *buffer,
              int32_t sectors_to_read);
int disk_close(struct disk_t *pdisk);

struct volume_t *fat_open(struct disk_t *pdisk, uint32_t first_sector);
int fat_close(struct volume_t *pvolume);

struct dir_t *dir_open(struct volume_t *pvolume, const char *dir_path);
int dir_read(struct dir_t *pdir, struct dir_entry_t *pentry);
int dir_close(struct dir_t *pdir);

#endif
