/* ------------------------------
   $Id: mkhd.c,v 1.4 2004/10/12 09:16:57 marquet Exp $
   ------------------------------------------------------------

   Create and intialize a drive using the hardware simulator.
   Philippe Marquet, october 2002

   A minimal example of a program using the ATA interface.
   It is given to the students as such.
   
*/

#include <assert.h>
#include "drive.h"


static void empty_it(){
    return;
}

void dmps();
void frmt();

void chk_hda(){
    int sectorsize;
    _out(HDA_CMDREG,CMD_DSKINFO);
    sectorsize = (_in(HDA_DATAREGS+4) << 8) +  _in(HDA_DATAREGS+5);
    assert(sectorsize==SECTORSIZE);
}

int main(int argc, char **argv)
{
    unsigned int i;
    unsigned int c,s;
    c=0;
    s=0;
    /* init hardware */
    if(init_hardware("hardware.ini") == 0) {
	fprintf(stderr, "Error in hardware initialization\n");
	exit(EXIT_FAILURE);
    }
    
    /* Interreupt handlers */
    for(i=0; i<16; i++)
	IRQVECTOR[i] = empty_it;

    /* Allows all IT */
    _mask(1);
    chk_hda();


    /*read a sector and print it and format the disk*/
    dmps(c,s);
    frmt();
    
    /*printf("Lecture du secteur 0\n");
    read_sector(c,s,buf);
    dump(buf,SECTORSIZE,1,0);
    printf("Affichage du secteur 1 reecrit\n");
    write_sector(c,1,buf);
    read_sector(c,1,buf);
    dump(buf,SECTORSIZE,1,0);
    printf("Affichage du secteur 2 formate \n");
    format_sector(c,2,0);
    read_sector(c,2,buf);
    dump(buf,SECTORSIZE,1,0);*/
    

    /* and exit! */
    exit(EXIT_SUCCESS);
}

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
    
    for(j=0;j<nbCylinder;j++){
	for (i=0;i<nbSector;i++){
	  /*format one sector of the disk
	    _out(HDA_DATAREGS,(1>>8) & 0xFF);
	    _out(HDA_DATAREGS+1, 1 & 0xFF);
	    _out(HDA_DATAREGS+2,0>>24 & 0xFF);
	    _out(HDA_DATAREGS+3, 0>>16 & 0xFF);
	    _out(HDA_DATAREGS+4,0>>8 & 0xFF);
	    _out(HDA_DATAREGS+5, 0 & 0xFF);
	    _out(HDA_CMDREG,CMD_FORMAT);
	    _sleep(HDA_IRQ);*/
	  format_sector(j,i,0);
	}
    }
}
