#define AVR_DRIVER_IMPLEMENTATION
#define FSW 1
#define BUFFER_SIZE (256/FSW)
#include "avr.h"
#include <stdint.h>

// define the  Mmemory 
volatile uint8_t buffer[BUFFER_SIZE];
volatile uint16_t active_buffer_size=0;
volatile uint16_t bufferIndex =0;
int main(){
  AVR_DRIVER_INIT();
  uint16_t count=0; 
  uint8_t buffer[BUFFER_SIZE];
  for (uint16_t i=0;i<=0x0FF;i+=FSW){
    if (count<BUFFER_SIZE){ 
      buffer[count++]=EEPROM_READ(i);
    }
  }
  active_buffer_size=count;
  // we need to pump this is into the pwm to simulate a dac we are using the changeing of the pulse to feed into a  filter

  while(1){
  // main code 
  __asm__ __volatile__ ("wdr");
  }
  return 0;  
}
