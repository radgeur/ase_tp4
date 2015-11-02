/* ------------------------------
   $Id: mkhd.c,v 1.4 2004/10/12 09:16:57 marquet Exp $
   ------------------------------------------------------------

   Create and intialize a drive using the hardware simulator.
   Philippe Marquet, october 2002

   A minimal example of a program using the ATA interface.
   It is given to the students as such.
   
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "hardware.h"
#include <assert.h>
#define SECTORSIZE 256
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14


/* dump buffer to stdout,
   and octal dump if octal_dump; an ascii dump if ascii_dump! */
static void
dump(unsigned char *buffer,
     unsigned int buffer_size,
     int ascii_dump,
     int octal_dump) 
{
    int i,j;
    
    for (i=0; i<buffer_size; i+=16) {
	/* offset */
	printf("%.8o",i);

	/* octal dump */
	if (octal_dump) {
	    for(j=0; j<8; j++)
		printf(" %.2x", buffer[i+j]);
	    printf(" - ");
	    
	    for( ; j<16; j++)
		printf(" %.2x", buffer[i+j]);
	    
	    printf("\n");
	}
	/* ascii dump */
	if (ascii_dump) {
	    printf("%8c", ' ');
	    
	    for(j=0; j<8; j++)
		printf(" %1c ", isprint(buffer[i+j])?buffer[i+j]:' ');
	    printf(" - ");
	    
	    for( ; j<16; j++)
		printf(" %1c ", isprint(buffer[i+j])?buffer[i+j]:' ');
	    
	    printf("\n");
	}
	
    }
}


static void empty_it()
{
  return;
}

void dmps();

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
    c=1;
    s=42;
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
    
    dmps(c,s);

    /* and exit! */
    exit(EXIT_SUCCESS);
}


void dmps (int cylinder, int sector){

    /*Move the cursor */
    _out(HDA_DATAREGS,(cylinder>>8) & 0xFF);
    _out(HDA_DATAREGS+1,cylinder & 0xFF);
    _out(HDA_DATAREGS+2,(sector>>8) & 0xFF);
    _out(HDA_DATAREGS+3,sector & 0xFF);
    _out(HDA_CMDREG,CMD_SEEK);
    _sleep(HDA_IRQ);

    /*Read the sector*/
    _out(HDA_DATAREGS,0);
    _out(HDA_DATAREGS+1,1);
    _out(HDA_CMDREG,CMD_READ);
    _sleep(HDA_IRQ);

    /*Print the sector*/
    dump(MASTERBUFFER,SECTORSIZE,1,0);
  
}
