#ifndef _SUPER_
#define _SUPER_

#include "mbr.h"

#define SUPER_MAGIC 0xCAFEBABE
#define BLOC_NULL 0
#define SUPER 0

struct super_s {
  unsigned super_first_free;
  unsigned super_nb_free;
  unsigned super_magic;
};

struct super_s super;

struct free_bloc_s{
	unsigned Fb_size;
	unsigned Fb_next;
};

extern void init_vol();
extern void save_super();
extern int load_super(unsigned int vol);
extern unsigned int new_bloc();
extern void free_bloc(unsigned int bloc);
#endif