#include "drive.h"

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer){
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
    memcpy(buffer,MASTERBUFFER,SECTORSIZE);

}

void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer){}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value){}

/* dump buffer to stdout,
   and octal dump if octal_dump; an ascii dump if ascii_dump! */
void dump(unsigned char *buffer,
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
