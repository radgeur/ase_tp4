#include "inode.h"


static void empty_it(){
    return;
}

void chk_hda(){
    int sectorsize;
    _out(HDA_CMDREG,CMD_DSKINFO);
    sectorsize = (_in(HDA_DATAREGS+4) << 8) +  _in(HDA_DATAREGS+5);
    assert(sectorsize==SECTORSIZE);
}

void dvol();
void mbrvol(unsigned nbblocs, unsigned firstCylinder, unsigned firstSector);

int main(){
    int i;
    /* init hardware */
    if(init_hardware("hardware.ini") == 0) {
	fprintf(stderr, "Error in hardware initialization\n");
	exit(EXIT_FAILURE);
    }
    
    /* Interrupt handlers */
    for(i=0; i<16; i++)
	IRQVECTOR[i] = empty_it;

    /* Allows all IT */
    _mask(1);
    chk_hda();
    printf("%i", CURRENT_VOLUME);
    mbrvol(4,1,7);
    mbrvol(12,4,3);
    dvol();
    exit(EXIT_SUCCESS);
}


/*display all the volumes*/
void dvol(){
    unsigned nb_vol, i;
    nb_vol = mbr.mbr_nb_vol;
    printf("%i volumes\n", nb_vol);
    for (i=0;i<nb_vol;i++){
	printf("vol %i  (%i,%i)  %i blocs\n",i, mbr.mbr_vol[i].vol_first_cylinder, mbr.mbr_vol[i].vol_first_sector, mbr.mbr_vol[i].vol_nb_bloc);
    }
}

/*create a new volume*/
void mbrvol(unsigned nbblocs, unsigned firstCylinder, unsigned firstSector){
    struct vol_s vol;
    load_mbr();
    vol.vol_first_sector=firstSector;
    vol.vol_first_cylinder=firstCylinder;
    vol.vol_nb_bloc=nbblocs;
    vol.type=STD;
    mbr.mbr_vol[mbr.mbr_nb_vol]=vol;
    mbr.mbr_nb_vol++;
    save_mbr();
}
