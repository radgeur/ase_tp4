#include "mkvol.h"
#include "super.h"
#include "lib_hardware.h"

int main (){
  unsigned int i, free, random, j, h;
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

  mbrvol(20,2,1);
  mbrvol(6,5,4);
  
  init_super();
  free = super.nb_free;

  /*fill al the volume*/
  while(super.nb_free != 0)
    new_bloc();
  printf("the current volume has actually %d free blocs\n", super.nb_free);
  random = rand() % free;
  
  /*free a random number of blocs*/
  for(j=1; j<=random; j++)
    free_bloc(j);
  printf("%d\n", random);
  printf("the current volume has now %d free blocs\n",super.nb_free);
  
  /*fill again the volume */
  while(super.nb_free != 0){
    new_bloc();
    h++;
  }

  printf("%d blocs are filled\n", h);
	
  return 1;
}
