#include <stdint.h>
#define SREG_REG                (*(volatile uint8_t*)0x005F)// we write to  to as  value
#define SPH_REG                 (*(volatile uint8_t*)0x005E)
#define SPL_REG                 (*(volatile uint8_t*)0x005D)
#define EEARL_REG               (*(volatile uint8_t*)0x0041)
#define EEPROM_Data_REG         (*(volatile uint8_t*)0x0040)// use for writeing datat to be store at 0x8 per 
#define EEPROM_Control_REG      (*(volatile uint8_t*)0x003F)
#define EEPROM_Control_Read_REG (*(volatile uint8_t*)0x001F)
#define SPMCSR_read             (*(volatile uint8_t*)0x0037)
#define GPIOR2                  (*(volatile uint8_t*)0x004B)
#define GPIOR1                  (*(volatile uint8_t*)0x004A)
#define GPIOR0                  (*(volatile uint8_t*)0x003E)
#define CLKPR                   (*(volatile uint8_t*)0x0061)




#define Clock_Frequency  8000000
typedef enum {Erase_and_Write,Erase,Write} modes_t;

uint8_t SET_EEPROM_MODE(modes_t mode ,uint8_t EEPROM_Control_REG_value){
  switch (mode){
    case Erase_and_Write:break;
    case Erase:
      EEPROM_Control_REG_value |= 0x10;
      break;
    case Write:
      EEPROM_Control_REG_value |= 0x20;
      break;
    default:
      return -1;
      break;
  }
  return EEPROM_Control_REG_value;
}
static inline void WAIT_AMOUNT_OF_CLOCK_CYCLES(int8_t Amount_of_clock_cycles){
  // caluute the clock Frequnecy 1/F = the amount time for 1 cycle
  while(Amount_of_clock_cycles--){
    __asm__ volatile ("nop");
  }
}
int8_t  EEPROM_WRITE_ENABLE(){
  // consider a while but it  be nice  to not have to  have in a loop
  // Wait until EEPE becomes zero.
  if ((EEPROM_Control_Read_REG&0x2)==0x0){
    // Wait until SELFPRGEN in SPMCSR becomes zero.
    if ((SPMCSR_read&0x0)==0){
      // Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR.
      EEPROM_Control_REG=0x6;

      // Within four clock cycles after setting EEMPE, write a logical one to EEPE.
      WAIT_AMOUNT_OF_CLOCK_CYCLES(4);
      EEPROM_Control_REG =0x2;
      return 0;
    }

  }
  else {
    return -1;    
    //break //in case of we write a  while loop
  }
}
void EEPROM_WRITE(uint16_t uiAddress,unsigned char ucData){

  EEARL_REG=uiAddress;
  EEPROM_Data_REG=ucData;
}
void AVR_DRIVER_INIT(){
  // set the global interupt enable to be on.
  SREG_REG= 0x80;
  // set Stack pointer high to the highest 
  SPH_REG = 0xFF;
  // set Stack pointer low to the highest 
  SPL_REG =0x8;
  // set_ EEARL to 256 bytes
  EEARL_REG =0x8;
  // set the EEPROM_Control_REG_value
  EEPROM_Control_REG=0xC;
  EEPROM_Control_REG=SET_EEPROM_MODE(Erase_and_Write,EEPROM_Control_REG);
  EEPROM_WRITE_ENABLE();

}
int main(){
  AVR_DRIVER_INIT();
  return 0;
}
