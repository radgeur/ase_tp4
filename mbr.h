#ifndef _MBR_
#define _MBR_

#include <assert.h>
#include "drive.h"

#define MAXVOL 8
#define MBR_MAGIC 0xCAFEBABE
#define NBSECTORPERCYLINDER 16

static struct mbr_s mbr;

enum vol_type_e {STD, ANX, OTHER};

struct vol_s {
  unsigned vol_first_sector;
  unsigned vol_first_cylinder;
  unsigned vol_nb_bloc;
  enum vol_type_e type;
};

struct mbr_s{
  struct vol_s mbr_vol[MAXVOL];
  unsigned mbr_nb_vol;
  unsigned mbr_magic;	
};

extern int load_mbr();
extern void save_mbr();
extern int sector_of_bloc(unsigned int vol, unsigned int nbloc);
extern int cylinder_of_bloc(unsigned int vol, unsigned int nbloc);
extern void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
extern void read_nbloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer, int n);
extern void write_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
extern void write_nbloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer, int n);
extern void format_bloc(unsigned int vol);

#endif
