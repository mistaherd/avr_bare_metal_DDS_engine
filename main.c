#define AVR_DRIVER_IMPLEMENTATION
#define FSW 1
#define BUFFER_SIZE (256/FSW)
#include "avr.h"
#include <stdint.h>
int main(){
  AVR_DRIVER_INIT();
  int count=0; 

  uint8_t buffer[BUFFER_SIZE];
  for (int i=0;i<=0x0FF;i+=FSW){
    if (count<BUFFER_SIZE) buffer[count++]=EEPROM_READ((uint16_t*)i);
  }
  return 0;  
}
