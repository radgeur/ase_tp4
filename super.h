#ifndef _SUPER_
#define _SUPER_

#include "mbr.h"

#define SUPER_MAGIC 0xCAFEBABE
#define BLOC_NULL 0
#define SUPER 0
#define CURRENT_VOLUME atoi(getenv("CURRENT_VOLUME"))

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

extern void init_super();
extern void save_super();
extern int load_super();
extern unsigned int new_bloc();
extern unsigned int new_bloc_zero();
extern void free_bloc(unsigned int bloc);
extern void free_blocs(unsigned tbloc[], unsigned tsize);
#endif
