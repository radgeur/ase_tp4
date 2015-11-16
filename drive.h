#ifndef _DRIVE_
#define _DRIVE_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hardware.h"
#define SECTORSIZE 256
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14

extern void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
extern void read_nsector(unsigned int cylinder, unsigned int sector, unsigned char *buffer, unsigned n);
extern void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer);
extern void write_nsector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer, unsigned n);
extern void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value);
extern void dump(unsigned char *buffer, unsigned int buffer_size, int ascii_dump, int octal_dump);


#endif
