#ifndef _MBR_
#define _MBR_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "drive.h"

#define MAXVOL = 5
#define MBR_MAGIC = 42

enum vol_type_e {VOLTYPE_STD, VOLTYPE_ANX, VOLTYPE_OTHER};

struct vol_s {
  unsigned int vol_first_sector;
  unsigned int vol_first_cylinder;
  unsigned vol_n_bloc;
  enum vol_type_e vol_type;
};

struct MBR_s{
	struct vol_s mbr_vol[MAXVOL];
	unsigned int mbr_n_vol;
	unsigned mbr_magic;	
};

extern int load_mbr(); 
extern int sector_of_bloc(unsigned int vol, unsigned int nbloc);
extern int cylinder_of_bloc(unsigned int vol, unsigned int nbloc);
extern void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
extern void write_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
extern void format_bloc(unsigned int vol);

#endif