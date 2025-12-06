#define SREG_REG  (*(volatile uint8_t*)0x005F ))// we write to  to as  value
#define SPH_REG   (*(volatile uint8_t*)0x005E ))
#define SPL_REG   (*(volatile uint8_t*)0x005D)
#define EEARL_REG (*(volatile uint8_t*)0x0041)
#define EEPROM_Data_REG      (*(volatile uint8_t*)0x0040) // use for writeing datat to be store at 0x8 per 
#define EEPROM_Control_REG      (*(volatile uint8_t*)0x003F)
enum modes{Erase_and_write,Erase,Write};

int EEPROM_MODE(modes mode ,uint8_t EEPROM_Control_REG_value){
   switch (mode){
    case Erase_and_write:
      EEPROM_Control_REG_value &= ~0x30;
      break;
    case Erase:
      EEPROM_Control_REG_value |= 0x10;
      break;
    case Write:
      EEPROM_Control_REG_value |= 0x20;
      break;
    default:
      perror("Error while writeing EEPROM Modes");
      break;
  }
}
void avr_driver_init(){
  // set the global interupt enable to be on.
  SREG_REG |= 0x80;
  // set Stack pointer high to the highest 
  SPH_REG = 0xFF;
  // set Stack pointer low to the highest 
  SPL_REG =0x8;
  // set_ EEARL to 256 bytes
  EEARL_REG =0x8;
  
}
int main(){
  ardunio_driver_init();
  return 0;
}
