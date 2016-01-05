#include "lib_hardware.h"
#include "mkvol.h"

int main (){
  unsigned int i;
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
    
  mbrvol(4,2,1);
  mbrvol(6,5,4);
  dvol();

  return 1;
}
