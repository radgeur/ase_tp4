#include "mkvol.h"

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
    printf("add\n");
    vol.vol_first_sector=firstSector;
    vol.vol_first_cylinder=firstCylinder;
    vol.vol_nb_bloc=nbblocs;
    vol.type=STD;
    mbr.mbr_vol[mbr.mbr_nb_vol]=vol;
    mbr.mbr_nb_vol++;
    save_mbr();
}
