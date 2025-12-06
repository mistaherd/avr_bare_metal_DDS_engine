// base addr =0x0000
#define SMCR  (*(volatile uint8_t*)0x0033)
#define MCUCR (*(volatile uint8_t*)0x0035)
#define CLKPR (*(volatile uint8_t*)0x0061)
#define PRR   (*(volatile uint8_t*)0x0064)
#include <stdio.h>
#include <stdint.h>
void ardunio_driver_init(){
  SREG |= 080;
  // first we enable CLKPR by setting the 7th bit
  CLKPR |=0x80;
  // set the clk divisions to 1 bits
  CLKPR |=0x0;
  // enable sleep mode 
  SMCR|=0x1;
  //this is  so we have  a fucntion in our code to put the diffent mode
  //we need to put it into idle mode
  SMCR|=0x0;
  // lets adde brown out dectection
  // Write a logical 1 to both BODS and BODSE
  MCUCR|=0x60;
  // Write BODS to 1 and BODSE to 0 within 4 clock cycles
  MCUCR &=0x40;

  PRR |=0x3;

  PRR |=0x3;
}
//void 
int main(){
  for (int i=0;i<3;i++){
    printf("%d\t",i);
  }
  
  return 0;
} 
