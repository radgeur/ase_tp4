#ifndef _SUPER_
#define _SUPER_

#include "mbr.h"

#define SUPER_MAGIC 0xCAFEBABE
#define BLOC_NULL 0
#define SUPER 0

struct super_s {
  unsigned first_free;
  unsigned nb_free;
  unsigned magic;
};

struct super_s super;

struct free_bloc_s{
	unsigned size;
	unsigned next;
};

extern void init_vol();
extern void save_super();
extern int load_super(unsigned int vol);
extern unsigned int new_bloc();
extern void free_bloc(unsigned int bloc);
#endif
