#include <stdio.h>
#include <stdint.h>
#include <math.h>
int main(int argc, char *argv[]){
  if (argc >1){
    perror("Usage ./samplegen <number of samples> [options]\nOptions:\n1:\t sinewave (deafault)\n 2:\t cossinewave\n3:\t audio piease");
    return -1;
  }
int8_t options= 0;
  if (argc>2){
    options=argv[2];
  }

  return 0;
}
