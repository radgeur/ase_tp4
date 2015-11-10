#include "mbr.h"

int load_mbr(){
    char buffer[SECTORSIZE];
    assert(SECTORSIZE>=sizeof(struct mbr_s));
    read_sector(0,0,buffer);
    memcopy(&mbr,buffer,sizeof(struct mbr_s));
    if(mbr.mbr_magic!= MBR_MAGIC){
	mbr.mbr_nb_vol = 0;
	mbr.mbr_magic = MBR_MAGIC;
	return 0;
    }
    return 1;
}

int sector_of_bloc(unsigned int vol, unsigned int nbbloc){
    unsigned int s;
    s=(mbr.mbr_vol[vol].vol_first_sector+nbbloc)%NBSECTORPERCYLINDER;
    return s;
}

int cylinder_of_bloc(unsigned int vol, unsigned int nbbloc) {
    unsigned int c;
    c=(mbr.mbr_vol[vol].vol_first_cylinder + (mbr.mbr_vol[vol].vol_first_sector+nbbloc))%NBSECTORPERCYLINDER;
    return c;
}

void read_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer){
    assert(MAXVOL>vol);
    /*assert()*/;
    int c=cylinder_of_bloc(vol,nbloc);
    int s=sector_of_bloc(vol,nbloc);
    read_sector(c,s,buffer);
}

void write_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer){
    assert(MAXVOL>vol);
    /*assert()*/
    int c=cylinder_of_bloc(vol,nbloc);
    int s=sector_of_bloc(vol,nbloc);
    write_sector(c,s,buffer);
}
