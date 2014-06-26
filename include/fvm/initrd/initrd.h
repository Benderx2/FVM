#ifndef __INITRD_H
#define __INITRD_H
#include <stdint.h>
typedef struct
{
   uint32_t files; // The number of files in the ramdisk.
} initrd_header_t;

typedef struct
{
   uint8_t magic;     // Magic number, for error checking.
   char name[64];  // Filename.
   uint32_t offset;   // Offset in the initrd that the file starts.
   uint32_t length;   // Length of the file.
} initrd_file_header_t;
void load_file_from_disk(uint8_t* mem, const char* file_name, uint8_t* buffer);
#endif
