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
  int maxCylinder, maxSector;
  _out(HDA_CMDREG,CMD_DSKINFO);
  maxSector = (_in(HDA_DATAREGS+2)<<8) + _in(HDA_DATAREGS+3);
  maxCylinder = (_in(HDA_DATAREGS)<<8) + _in(HDA_DATAREGS+1);
  if(firstCylinder > maxCylinder || firstSector > maxSector) {
    printf("the number of the cylinder or the sector is higher than the max number of cylinder or sector on the disk. number max of cylinder : %d, number max of sector : %d.", maxCylinder, maxSector);
    return;
  }
  if(mbr.mbr_nb_vol >= MAXVOL){
    printf("you cannot add an other volume on this disk");
    return;
  }
  vol.vol_first_sector=firstSector;
  vol.vol_first_cylinder=firstCylinder;
  vol.vol_nb_bloc=nbblocs;
  vol.type=STD;
  mbr.mbr_vol[mbr.mbr_nb_vol]=vol;
  mbr.mbr_nb_vol++;
  save_mbr();
}
