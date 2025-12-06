#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
int32_t LFSR(int32_t reg,int32_t N){
  int32_t taps=0xB8;
  for(int i=0;i<N;i++){
    printf("reg: %d\n",reg);
    int32_t res=taps&reg;
    int32_t feedback_bit=((0b1<<7)&res)^((0b1<<5)&res)^((0b1<<4)&res)^((0b1<<3)&res)^((0b1<<0)&res);
    reg=reg>>1;
    reg |=(feedback_bit<<7);
  
  }
  return reg;
}
int main(){

  int32_t reg=LFSR(9,0xF);
  return 0;
}
