#ifndef FILE_READER_H
#define FILE_READER_H

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SECTOR_SIZE 512
struct volume_t {
  struct disk_t *pdisk;
  int16_t bytes_per_sector;
  uint8_t sectors_per_cluster;
  uint16_t reserved_sectors;
  uint8_t fat_count;
  uint16_t sectors_per_fat;
  uint16_t root_dir_capacity;
  uint16_t logical_sectors16;
  uint32_t logical_sectors32;
};
struct file_t;
struct disk_t {
  int fd;
};
struct dir_t;

struct dir_entry_t {
  char *name; //- nazwa pliku/katalogu (w przypadku pliku nazwa ma być z kropką
              //i rozszerzeniem), bez nadmiarowych spacji i zakończona
              // terminatorem,
  size_t size;             // - rozmiar pliku/katalogu w bajtach,
  uint8_t is_archived : 1; // - wartość atrybutu: plik zarchiwizowany (0 lub 1),
  uint8_t is_readonly
      : 1;               //- wartość atrybutu : plik tylko do odczytu(0 lub 1),
  uint8_t is_system : 1; // wartość atrybutu : plik jest systemowy(0 lub 1),
  uint8_t is_hidden : 1; //- wartość atrybutu : plik jest ukryty(0 lub 1),
  uint8_t is_directory : 1; // - wartość atrybutu : katalog(0 lub 1).
};

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
