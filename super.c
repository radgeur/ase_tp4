#include "super.h"

void save_super(){
    write_nbloc(CURRENT_VOLUME,SUPER, (unsigned char *) &super,sizeof(struct super_s));
}

void init_super(){
    struct free_bloc_s free;
    super.first_free=1;
    super.nb_free=mbr.mbr_vol[CURRENT_VOL].vol_size -1;
    super.magic = SUPER_MAGIC;
    write_nbloc(CURRENT_VOLUME,SUPER, (unsigned char *) &super,sizeof(struct super_s));
    free.size=super.nb_free;
    free.next=BLOC_NULL;
    write_nbloc(CURRENT_VOLUME,1,(unsigned char *) &free, sizeof(struct free_bloc_s));
}

int load_super(){
    read_nbloc(CURRENT_VOLUME,SUPER,(unsigned char *) &super, sizeof(struct super_s));
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
    write_nbloc(super.first_free,res,sizeof(struct free_bloc_s), (unsigned char *) &free);
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
