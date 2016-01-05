#ifndef _LIB_HARDWARE_
#define _LIB_HARDWARE_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "drive.h"
#include "hardware.h"
#define SECTORSIZE 256
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14

extern void dmps (int cylinder, int sector);
extern void frmt ();
extern void empty_it();
extern void chk_hda();

#endif
