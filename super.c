#include "super.h"

void save_vol(){
	write_bloc(SUPER,&super,sizeof(super));
}

void init_vol(){
	super.super_first_free=1;
	super.super_nb_free=mbr.mbr_vol[Current_vol].vol_size -1;
	super.super_magic = SUPER_MAGIC;
	/*write_bloc(SUPER,&super,sizeof(super)); Cest save_super()*/
	struct free_bloc_s Fb;
	Fb.Fb_size=super.super_nb_free;
	Fb.Fb_next=BLOC_NULL;
	write_bloc(1,&FB,sizeof(Fb));
}

int load_super(unsigned int vol){
	return 1;
}

unsigned int new_bloc(){
	unsigned res;
	if(super.super_nb_free==0){
		return BLOC_NULL;
	}
	read_bloc(super.super_first_free,&Fb,sizeof(Fb));
	res=super.super_first_free;
	super.super_nb_free--;
	if(Fb.Fb_size ==1){
		super.super_first_free = Fb.Fb_next;
		return res;
	}
	super.super_first_free++;
	Fb.Fb_size--;
	write_bloc(super.super_first_free,&Fb,sizeof(Fb));
	return res;
}

void free_bloc(unsigned int bloc){
	struct free_bloc_s new;
	new.Fb_size=1;
	new.Fb_next=super.super_first_free;
	super.super_first_free=bloc;
	super.super_nb_free++;
}