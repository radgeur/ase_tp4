#include "super.h"

/*save the super bloc */
void save_super(){
    write_nbloc(CURRENT_VOLUME,SUPER, (unsigned char *) &super,sizeof(struct super_s));
}

/*initialize a super bloc*/
void init_super(){
    struct free_bloc_s free;
    super.first_free=1;
    super.nb_free=mbr.mbr_vol[CURRENT_VOLUME].vol_nb_bloc -1;
    super.magic = SUPER_MAGIC;
    write_nbloc(CURRENT_VOLUME,SUPER, (unsigned char *) &super,sizeof(struct super_s));
    free.size=super.nb_free;
    free.next=BLOC_NULL;
    write_nbloc(CURRENT_VOLUME,1,(unsigned char *) &free, sizeof(struct free_bloc_s));
}

/*load a super bloc*/
int load_super(){
    read_nbloc(CURRENT_VOLUME,SUPER,(unsigned char *) &super, sizeof(struct super_s));
    return 1;
}

/*return a new free bloc*/
unsigned int new_bloc(){
    unsigned res;
    struct free_bloc_s free;
    if(super.nb_free==0){
	return BLOC_NULL;
    }
    read_nbloc(CURRENT_VOLUME,super.first_free,(unsigned char *) &free ,sizeof(struct free_bloc_s));
    if(free.size == 1){
	res=super.first_free;
	super.nb_free--;
	super.first_free = free.next;
	return res;
    }
    res=super.first_free;
    super.nb_free--;
    super.first_free++;
    free.size--;
    write_nbloc(CURRENT_VOLUME,super.first_free,(unsigned char *) &free,sizeof(struct free_bloc_s));
    /*printf("res = %d\n super.nb_free = %d\n super.first_free = %d\n free.size = %d\n",res, super.nb_free, super.first_free, free.size);*/
    return res;
}

/*free a bloc*/
void free_bloc(unsigned int bloc){
    struct free_bloc_s res;
    /*0 is allowed to superbloc*/
    if(!bloc){
	printf("The superbloc can't be free!");
	exit(EXIT_FAILURE);
    }
    res.size=1;
    res.next=super.first_free;
    write_nbloc(CURRENT_VOLUME,bloc, (unsigned char *)&res, sizeof(struct free_bloc_s));
    super.first_free=bloc;
    super.nb_free++;
    /*printf("res.next = %d\n super.first_free = %d\n super.nb_free = %d\n", res.next, super.first_free, super.nb_free);*/
}

/*free tsize bloc(s)*/
void free_blocs(unsigned tbloc[], unsigned tsize){
    int i;
    for(i=0; i<tsize; i++){
	free_bloc(tbloc[i]);
    }
}

/*initialize a new bloc with all 0 inside*/
unsigned new_bloc_zero(){
    int res;
    unsigned char buf[SECTORSIZE] = {0};
    res=new_bloc();
    write_bloc(CURRENT_VOLUME, res, buf);
    return res;
}
