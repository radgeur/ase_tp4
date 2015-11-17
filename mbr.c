#include "mbr.h"

/*Initialize the mbr*/
int load_mbr(){
    unsigned char buffer[SECTORSIZE];
    assert(SECTORSIZE>=sizeof(struct mbr_s));
    read_sector(0,0,buffer);
    memcpy(&mbr,buffer,sizeof(struct mbr_s));
    if(mbr.mbr_magic!= MBR_MAGIC){
	mbr.mbr_nb_vol = 0;
	mbr.mbr_magic = MBR_MAGIC;
	return 0;
    }
    return 1;
}

/*Save the mbr*/
void save_mbr(){
    unsigned char buffer[SECTORSIZE];
    memcpy(buffer,&mbr,sizeof(struct mbr_s));
    write_bloc(0,0,buffer);
}


/*Return the sector number of a bloc*/
int sector_of_bloc(unsigned int vol, unsigned int nbbloc){
    unsigned int s;
    s=(mbr.mbr_vol[vol].vol_first_sector+nbbloc)%NBSECTORPERCYLINDER;
    return s;
}

/*Return the cylinder number of a bloc*/
int cylinder_of_bloc(unsigned int vol, unsigned int nbbloc) {
    unsigned int c;
    c=(mbr.mbr_vol[vol].vol_first_cylinder + (mbr.mbr_vol[vol].vol_first_sector+nbbloc))%NBSECTORPERCYLINDER;
    return c;
}

/*Read a bloc*/
void read_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer){
    int c,s;
    assert(MAXVOL>vol);
    assert(mbr.mbr_vol[vol].vol_nb_bloc>=nbbloc);
    c=cylinder_of_bloc(vol,nbbloc);
    s=sector_of_bloc(vol,nbbloc);
    read_sector(c,s,buffer);
}

/*Read only n bytes of a bloc*/
void read_nbloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer, int n){
    int c,s;
    assert(MAXVOL>vol);
    assert(mbr.mbr_vol[vol].vol_nb_bloc>=nbbloc);
    c=cylinder_of_bloc(vol,nbbloc);
    s=sector_of_bloc(vol,nbbloc);
    read_nsector(c,s,buffer,n);
}

/*Write on a bloc*/
void write_bloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer){
    int c,s;
    assert(MAXVOL>vol);
    assert(mbr.mbr_vol[vol].vol_nb_bloc>=nbbloc);
    c=cylinder_of_bloc(vol,nbbloc);
    s=sector_of_bloc(vol,nbbloc);
    write_sector(c,s,buffer);
}

/*Write only n bytes on the bloc*/
void write_nbloc(unsigned int vol, unsigned int nbbloc, unsigned char *buffer, int n){
    int c,s;
    assert(MAXVOL>vol);
    assert(mbr.mbr_vol[vol].vol_nb_bloc>=nbbloc);
    c=cylinder_of_bloc(vol,nbbloc);
    s=sector_of_bloc(vol,nbbloc);
    write_nsector(c,s,buffer,n);
}

/*Format a volume*/
void format_vol(unsigned int vol){
    unsigned nbbloc;
    int c,s;
    nbbloc = mbr.mbr_vol[vol].vol_nb_bloc;
    c=cylinder_of_bloc(vol,nbbloc);
    s=sector_of_bloc(vol,nbbloc);
    format_sector(c,s,0);
}

