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
#include "lib_hardware.h"


static void empty_it(){
    return;
}

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
    

    /* and exit! */
    exit(EXIT_SUCCESS);
}
