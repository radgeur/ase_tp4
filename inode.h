#ifndef _INODE_
#define _INODE_

#include "super.h"

#define NDIRECT 10
#define NBBLOCPARBLOC 4 /*BLOC_SIZE/sizeof(unsigned int)*/

enum file_type_e {FILE,DIR};

struct inode_s {
    enum file_type_e type;
    unsigned size;
    unsigned direct[NDIRECT];
    unsigned indirect;
    unsigned two_indirect;
};

extern unsigned int create_inode(enum file_type_e type);
extern int delete_inode(unsigned int inumber);
extern void read_inode(unsigned int inumber, struct inode_s inode);
extern void write_inode(unsigned int inumber, struct inode_s inode);
extern unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, bool_t do_allocate);

#endif


  
