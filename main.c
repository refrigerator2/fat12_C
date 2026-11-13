#include "file_reader.h"
/*
 * Demo of the FAT12 reader.
 * Usage: ./main [image] [file] [subdirectory]
 * Defaults: subtract_fat12_volume.img, TAIL, no subdirectory.
 */
int main(int argc, char **argv) {
  const char *image = argc > 1 ? argv[1] : "subtract_fat12_volume.img";
  const char *file_name = argc > 2 ? argv[2] : "TAIL";

  /* 1. Open the disk image and the FAT12 volume that starts at sector 0 */
  struct disk_t *disk = disk_open_from_file(image);
  if (!disk)
    return 1;
  struct volume_t *volume = fat_open(disk, 0);
  if (!volume) {
    disk_close(disk);
    return 1;
  }
  printf("Volume: %u bytes per sector, %u sectors per cluster\n\n",
         volume->ss->bytes_per_sector, volume->ss->sectors_per_cluster);

  /* 2. List the root directory */
  struct dir_t *dir = dir_open(volume, "\\");
  struct dir_entry_t entry;
  printf("Root directory:\n");
  while (dir_read(dir, &entry) == 0)
    printf("  %.8s %.3s  %s  %u bytes\n", entry.name, entry.ext,
           (entry.attrs & 0x10) ? "<DIR>" : "     ", (unsigned)entry.size);
  dir_close(dir);

  /* 3. List a subdirectory, if one was given */
  if (argc > 3) {
    dir = dir_open(volume, argv[3]);
    if (dir) {
      printf("\nDirectory %s:\n", argv[3]);
      while (dir_read(dir, &entry) == 0)
        printf("  %.8s %.3s  %s  %u bytes\n", entry.name, entry.ext,
               (entry.attrs & 0x10) ? "<DIR>" : "     ", (unsigned)entry.size);
      dir_close(dir);
    }
  }

  /* 4. Open a file and read its beginning */
  printf("\nOpening %s\n", file_name);
  struct file_t *file = file_open(volume, file_name);
  if (file) {
    char buffer[33];
    size_t n = file_read(buffer, 1, 32, file);
    buffer[n] = '\0';
    printf("Size: %u bytes, first %zu bytes read: \"", (unsigned)file->size, n);
    for (size_t i = 0; i < n; i++)
      putchar(isprint((unsigned char)buffer[i]) ? buffer[i] : '.');
    printf("\"\n");

    /* 5. Jump to the middle of the file and read again */
    int32_t middle = (int32_t)(file->size / 2);
    if (file_seek(file, middle, SEEK_SET) == middle) {
      n = file_read(buffer, 1, 32, file);
      printf("Read %zu bytes at offset %d: \"", n, middle);
      for (size_t i = 0; i < n; i++)
        putchar(isprint((unsigned char)buffer[i]) ? buffer[i] : '.');
      printf("\"\n");
    }
    file_close(file);
  }

  /* 6. Errors are reported through errno */
  printf("\nOpening a file that does not exist:\n");
  if (!file_open(volume, "MISSING.TXT"))
    printf("file_open failed, errno = %d (%s)\n", errno, strerror(errno));

  fat_close(volume);
  disk_close(disk);
  return 0;
}
