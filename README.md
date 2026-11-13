# FAT12 file reader

A small read-only C library that reads files and directories from a FAT12 disk
image (for example a floppy image). It has no dependencies besides the C
standard library and POSIX (`open`, `read`, `lseek`).

## Files

| File | Purpose |
|---|---|
| `file_reader.h` | Structures and the public API |
| `file_reader.c` | Implementation |
| `main.c` | Demo program showing how to use the API |

## Structures

- `struct disk_t` - open image (`id` is the file descriptor, `sector_size`).
- `struct volume_t` - mounted volume: boot sector, FAT, root directory and the
  offsets needed to locate the data area.
- `struct dir_entry_t` - one 32-byte directory entry. `name` and `ext` are the
  padded 8+3 characters (not null-terminated), `attrs` holds the attribute
  bits, `young_word` is the first cluster and `size` the size in bytes.
- `struct file_t` / `struct dir_t` - state of an open file or directory.

Attribute bits: `0x01` read-only, `0x02` hidden, `0x04` system,
`0x08` volume label, `0x10` directory, `0x20` archive, `0x0F` long file name.

## API

| Function | Returns | Errors (`errno`) |
|---|---|---|
| `disk_open_from_file(path)` | `struct disk_t *` or `NULL` | `EFAULT`, `ENOENT`, `ENOMEM` |
| `disk_read(disk, first_sector, buf, count)` | number of sectors read, `-1` on error | `EFAULT`, `ERANGE` (outside of the image) |
| `disk_close(disk)` | `0` or `-1` | `EFAULT` |
| `fat_open(disk, first_sector)` | `struct volume_t *` or `NULL` | `EFAULT`, `ENOMEM`, `EINVAL` (sector size mismatch), `ERANGE` (image too short) |
| `fat_close(volume)` | `0` or `-1` | `EFAULT` |
| `file_open(volume, name)` | `struct file_t *` or `NULL` | `EFAULT`, `ENOMEM`, `ENOENT`, `EISDIR`, `EINVAL` |
| `file_read(ptr, size, nmemb, file)` | number of elements read (like `fread`), `0` at end of file, `(size_t)-1` on error | `EFAULT`, `EIO` (broken cluster chain) |
| `file_seek(file, offset, whence)` | new position, `-1` on error | `EFAULT`, `EINVAL` (bad `whence`), `ENXIO` (position outside the file) |
| `file_close(file)` | `0` or `-1` | `EFAULT` |
| `dir_open(volume, path)` | `struct dir_t *` or `NULL` | `EFAULT`, `ENOMEM`, `ENOENT`, `ENOTDIR` |
| `dir_read(dir, entry)` | `0` entry returned, `1` no more entries, `-1` error | `EFAULT`, `EIO` |
| `dir_close(dir)` | `0` or `-1` | `EFAULT` |

Every error is also printed to `stderr` with `perror`. `dir_read` skips deleted
entries, long file name entries and the volume label.

## Build

```sh
gcc -std=c11 -Wall -Wextra -pedantic -D_GNU_SOURCE \
    file_reader.c main.c -o main
```

## Usage

```sh
./main [image] [file] [subdirectory]
```

Defaults: `subtract_fat12_volume.img`, file `TAIL`, no subdirectory. The demo
prints the volume parameters, lists the root directory (and the subdirectory,
if given), reads the beginning of the file, seeks to its middle, and shows an
error caused by opening a file that does not exist.

Minimal example:

```c
struct disk_t *disk = disk_open_from_file("image.img");
struct volume_t *vol = fat_open(disk, 0);

struct dir_t *dir = dir_open(vol, "\\");      /* "\\" is the root directory */
struct dir_entry_t entry;
while (dir_read(dir, &entry) == 0)
    printf("%.8s %.3s %u\n", entry.name, entry.ext, (unsigned)entry.size);
dir_close(dir);

struct file_t *file = file_open(vol, "TAIL");
char buf[64];
size_t n = file_read(buf, 1, sizeof buf, file);
file_close(file);

fat_close(vol);
disk_close(disk);
```

## Limitations

- Read-only, FAT12 only, sector size up to 512 bytes.
- `file_open` looks for the file in the root directory only.
- `dir_open` accepts `"\\"` for the root directory or the name of a directory
  located in the root (for example `"SUBDIR"`). Deeper paths are not supported.
- Only short 8.3 names are supported; long file name entries are skipped.
- `file_seek` rejects a position equal to or beyond the file size (`ENXIO`).
