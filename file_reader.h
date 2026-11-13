#ifndef FILE_READER_H
#define FILE_READER_H
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_EXTENSION_LEN 3
#define MAX_FILE_NAME_LEN 8

struct volume_t {
  struct disk_t *did;
  uint32_t fsector;
  struct supersector *ss;
  struct dir_entry_t *root_dir;
  uint8_t *fat_table;
  uint32_t root_offset;
  uint32_t fat_offset;
  uint32_t data_offset_sectors;
};
struct file_t {
  uint8_t status;
  uint16_t first_cluster;
  uint32_t size;
  struct volume_t *vol;
  uint16_t current_cluster;
  uint32_t offset;
};
struct disk_t {
  int id;
  uint16_t sector_size;
};
struct dir_t {
  uint16_t first_cluster;
  uint16_t current_cluster;
  uint32_t size;
  struct volume_t *vol;
  uint32_t offset;
};

struct dir_entry_t {
  char name[MAX_FILE_NAME_LEN];
  char ext[MAX_EXTENSION_LEN];
  uint8_t attrs;
  uint8_t reserved;
  uint8_t creation_time_milisec;
  uint16_t creation_time;
  uint16_t creation_day;
  uint16_t last_access_date;
  uint16_t elder_word;
  uint16_t last_change_time;
  uint16_t last_change_date;
  uint16_t young_word;
  uint32_t size;
} __attribute__((packed));

struct supersector {
  uint8_t jmp_boot[3];
  char oem_name[8];
  uint16_t bytes_per_sector;
  uint8_t sectors_per_cluster;
  uint16_t reserved_sectors;
  uint8_t num_fats;
  uint16_t root_entries;
  uint16_t total_sectors_16;
  uint8_t media_descriptor;
  uint16_t sectors_per_fat;
  uint16_t sectors_per_track;
  uint16_t num_heads;
  uint32_t hidden_sectors;
  uint32_t total_sectors_32;

  uint8_t drive_number;
  uint8_t reserved;
  uint8_t boot_signature;
  uint32_t volume_id;
  char volume_label[11];
  char fs_type[8];

  uint8_t boot_code[448];
  uint16_t signature;
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
