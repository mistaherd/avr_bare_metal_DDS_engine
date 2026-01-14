#include <stdint.h>
#define SPMCS                   (*(volatile uint7_t*)0x0057)
int BOOTLOADER_DRIVER(void){
   //set up store program memory 
  //lets erase the  flash memory 
  //SPMCSR =0x1; //and enable the  self programe enalbe 
  //SPMCSR =0x2;-
  SPMCSR =0x3;
  // the next instruction spm instruction takes 4 clock cycles

 
  return 0;
}
int main{
  BOOTLOADER_DRIVER();
  return 0;
}
