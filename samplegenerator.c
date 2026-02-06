#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"
int main(){
  size_t Sample_size=0xFF;
  const double M_PI =3.14159;
  
  Arena *arena =arena_init((Sample_size*sizeof(double))+1024);
  if (!arena )return 1;
  double *buffer=(double *)arena_alloc(arena,Sample_size*sizeof(double));
  if (!buffer){
    free_arena(arena);
    return 1;
  }
  for(int i=0;i<Sample_size;i++){
    buffer[i]=sin(((2*M_PI*1)*i)/Sample_size);

  }

 // printf("Output for array\n [%5f,",buffer[0]);
 // for (int i=1;i<Sample_size-1;i++){
 //   printf("%5f,",buffer[i]);

 // }
 // printf("%5f]\n",buffer[Sample_size-1]);
 FILE *Fileptr =fopen("Sinewave.hex","w");
  if (Fileptr ==NULL) {
    perror("error while opening file");
    free_arena(arena);
    return 1;
  }

  uint16_t addr=0x0000; //start address for eeprom
  for(size_t j=0;j<Sample_size;j+=16){
    size_t chunk =(Sample_size-j >16)?16 :Sample_size-j;
    // if  the sample size - index  is great then 16  return 16 if its not return Sample_size-i
    uint8_t checksum =chunk +(addr >>8)+(addr&0xff)+0x00;
    // a checksum  is a digit representing the sum of the corrects in a piece of 
    fprintf(Fileptr,":f%02X%04X00",(unsigned int)chunk,addr);
    for (size_t k=0;k<chunk;k++){
      uint8_t val = (uint8_t)((buffer[j + k] + 1.0) * 127.5);
      fprintf(Fileptr,"%02X",val);
      checksum +=val;

    }
    fprintf(Fileptr,"%02X\n",(uint8_t)(-checksum));
    addr+=(uint16_t)chunk;
  }
  fprintf(Fileptr,":00000001FF\n");
  if(fclose(Fileptr) !=0) perror("Error while closeing file");
  arena_reset(arena);
  free_arena(arena);

  return 0;
}
