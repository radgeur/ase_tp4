#include "mbr.h"

/*int load_mbr(){
	char buffer[SECTORSIZE];
	assert(SECTORSIZE>=sizeof(struct mbr_s));
	read_sector(0,0,buffer);
	memcopy(&mbr,buffer,sizeof(struct mbr_s));
	if(mbr.mbr_magic!= MBR_MAGIC){
		mbr.mbr_n_vol = 0;
		mbr.mbr_magic = MBR_MAGIC;
		return 0;
	}
	return 1;
*/

int sector_of_bloc(unsigned int vol, unsigned int nbloc){
	/*s =(Fs + b)%NSECTOR PAR CYLINDRE*/
	return 1;
}

int cylinder_of_bloc(unsigned int vol, unsigned int nbloc
	/*c=Fc+(Fs+b)/NSECTOR ¨PAR CYLINDRE*/
	return 1;
}

void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer){
	int c=cylinder_of_bloc(vol,nbloc);
	int s=sector_of_bloc(vol,nbloc);
	read_sector(c,s,buffer);
}

void write_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer){
	int c=cylinder_of_bloc(vol,nbloc);
	int s=sector_of_bloc(vol,nbloc);
	write_sector(c,s,buffer);
}