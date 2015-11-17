#include "super.h"

void save_vol(){
    write_bloc(SUPER,sizeof(struct super_s), (unsigned char *) &super);
}

void init_vol(){
    struct free_bloc_s free;
    super.first_free=1;
    super.nb_free=mbr.mbr_vol[CURRENT_VOL].vol_size -1;
    super.magic = SUPER_MAGIC;
    write_bloc(SUPER,sizeof(struct super_s), (unsigned char *) &super);
    free.size=super.nb_free;
    free.next=BLOC_NULL;
    write_bloc(1,sizeof(struct free_bloc_s), (unsigned char *) &free);
}

int load_super(unsigned int vol){
    return 1;
}

unsigned int new_bloc(){
    unsigned res;
    struct free_bloc_s free;
    if(super.nb_free==0){
	return BLOC_NULL;
    }
    read_bloc(super.first_free,sizeof(struct free_bloc_s), (unsigned char *) &free);
    res=super.first_free;
    super.nb_free--;
    if(free.size == 1){
	super.first_free = free.next;
	return res;
    }
    super.first_free++;
    free.size--;
    write_bloc(super.first_free,sizeof(struct free_bloc_s), (unsigned char *) &free);
    return res;
}

void free_bloc(unsigned int bloc){
    /*0 is allowed to superbloc*/
    if(!bloc){
	printf("The superbloc can't be free!");
	exit(EXIT_FAILURE);
    }
    struct free_bloc_s res;
    res.size=1;
    res.next=super.first_free;
    super.first_free=bloc;
    super.nb_free++;
}
