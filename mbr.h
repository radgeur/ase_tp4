#ifndef _MBR_
#define _MBR_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "drive.h"

#define MAXVOL 5
#define MBR_MAGIC 0xCAFEBABE
#define NBSECTORPERCYLINDER 16

enum vol_type_e {STD, ANX, OTHER};

struct vol_s {
    unsigned vol_first_sector;
    unsigned vol_first_cylinder;
    unsigned vol_nb_bloc;
    enum vol_type_e vol_type;
};

struct MBR_s{
    struct vol_s mbr_vol[MAXVOL];
    unsigned mbr_nb_vol;
    unsigned mbr_magic;	
};

extern int load_mbr(); 
extern int sector_of_bloc(unsigned int vol, unsigned int nbbloc);
extern int cylinder_of_bloc(unsigned int vol, unsigned int nbbloc);
extern void read_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer);
extern void write_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer);
extern void format_bloc(unsigned int vol);

#endif
