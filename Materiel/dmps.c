#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hardware.h"
#define SECTORSIZE 256
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14

/*print the content of a sector*/
void dmps (int cylinder, int sector){
    unsigned char buf[SECTORSIZE];

    read_sector(cylinder, sector, buf);

    /*Print the sector*/
    dump(buf,SECTORSIZE,1,0);
}
  

/*format all the disk*/
void frmt () {
    /*catch the number of sectors and cylinders*/
    int nbSector, nbCylinder,i,j;
    _out(HDA_CMDREG,CMD_DSKINFO);
    nbSector = (_in(HDA_DATAREGS+2)<<8) + _in(HDA_DATAREGS+3);
    nbCylinder = (_in(HDA_DATAREGS)<<8) + _in(HDA_DATAREGS+1);
    
    /*format the disk for all sector in all cylinders*/
    for(j=0;j<nbCylinder;j++){
	for (i=0;i<nbSector;i++){
	  format_sector(j,i,0);
	}
    }
}
