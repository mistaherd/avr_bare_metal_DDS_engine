#include <stdint.h>
#ifdef AVR_DRIVER_IMPLEMENTATION
// AVR Mmemories
#define GPIOR2                  (*(volatile uint8_t*)0x4B)
#define GPIOR1                  (*(volatile uint8_t*)0x4A)
#define GPIOR0                  (*(volatile uint8_t*)0x3E)
#define EEARL_REG               (*(volatile uint8_t*)0x41)
#define EEDR_W                  (*(volatile uint8_t*)0x40)
#define EEDR_R                  (*(volatile uint8_t*)0x20)// use for writeing datat to be store at 0x8 per 
#define EEPROM_Control_REG      (*(volatile uint8_t*)0x3F)
#define EEPROM_Control_Read_REG (*(volatile uint8_t*)0x1F)
// system Clock 
#define OSCCAL                  (*(volatile uint8_t*)0x66)
#define CLKPR                   (*(volatile uint8_t*)0x61)
// Power mangement 
#define SMCR                    (*(volatile uint8_t*)0x53)
#define PRR                     (*(volatile uint8_t*)0x64)
#define MCUCR                   (*(volatile uint8_t*)0x55)
// system control and reset
#define MCUSR                   (*(volatile uint8_t*))
#define WDTCSR                  (*(volatile uint8_t*)0x60)
#define EICRA                   (*(volatile uint8_t*)0x69)
#define EIMSK                   (*(volatile uint8_t*)0x3D)
#define EIFR                    (*(volatile uint8_t*)0x3C)
#define PCICR                   (*(volatile uint8_t*)0x68)
#define PCIFR                   (*(volatile uint8_t*)0x3B)
#define PCMSK2                  (*(volatile uint8_t*)0x6D)
#define PCMSK1                  (*(volatile uint8_t*)0x6C)
#define PCMSK0                  (*(volatile uint8_t*)0x6B)
#define TCCR0A                  (*(volatile uint8_t*)0x44) // mode 
#define TCCR0B                  (*(volatile uint8_t*)0x45) // control clock divider
#define TCNTO                   (*(volatile uint8_t*)0x46)
#define TCNTO_READ              (*(volatile uint8_t*)0x26)
#define TCCR1A                  (*(volatile uint8_t*)0x80)
#define TCCR1B                  (*(volatile uint8_t*)0x81)
#define TCCR1C                  (*(volatile uint8_t*)0x82)
#define TCNT1H                  (*(volatile uint8_t*)0x85)
#define TCNT1L                  (*(volatile uint8_t*)0x84)
#define OCR1AH                  (*(volatile uint8_t*)0x89)
#define OCR1AL                  (*(volatile uint8_t*)0x88)
#define OCR1BH                  (*(volatile uint8_t*)0x8B)
#define OCR1BL                  (*(volatile uint8_t*)0x8A)
#define ICR1H                   (*(volatile uint8_t*)0x87)
#define ICR1L                   (*(volatile uint8_t*)0x86)
#define TIMSK1                  (*(volatile uint8_t*)0x6F)
#define TIFR1                   (*(volatile uint8_t*)0x36)
#define GTCCR                   (*(volatile uint8_t*)0x43)
#define TCCR2A                  (*(volatile uint8_t*)0xB0)
#define TCCR2B                  (*(volatile uint8_t*)0xB1)
#define TCNT2                   (*(volatile uint8_t*)0xB2)
#define OCR2A                   (*(volatile uint8_t*)0xB3)
#define OCR2B                   (*(volatile uint8_t*)0xB4)
#define TIMSK2                  (*(volatile uint8_t*)0x70)
#define TIFR2                   (*(volatile uint8_t*)0x37)
#define ASSR                    (*(volatile uint8_t*)0xB6)
#define OCROA                   (*(volatile uint8_t*)0x47)
#define OCROB                   (*(volatile uint8_t*)0x48)
#define TIMSKO                  (*(volatile uint8_t*)0x6E)
#define TIFRO                   (*(volatile uint8_t*)0x35)
#define TIFRO_READ              (*(volatile uint8_t*)0x15)
#define SPMCS                   (*(volatile uint8_t*)0x57)
#define SREG_REG                (*(volatile uint8_t*)0x5F)// we write to  to as  value
#define SPH_REG                 (*(volatile uint8_t*)0x5E)
#define SPL_REG                 (*(volatile uint8_t*)0x5D)

#define SPMCSR_read             (*(volatile uint8_t*)0x37)
#define SPCR                    (*(volatile uint8_t*)0x4C)
#define SPSR                    (*(volatile uint8_t*)0x4D)
#define SPDR                    (*(volatile uint8_t*)0x4E)
// interupt
#define EICRA                   (*(volatile uint8_t*)0x69)
#define EMISK                   (*(volatile uint8_t*)0x3D)
#define EIFR                    (*(volatile uint8_t*)0x3C)
#define PCICR
// io
#define PORTB                   (*(volatile uint8_t*)0x25)
#define DDRB                    (*(volatile uint8_t*)0x24)
#define PINB                    (*(volatile uint8_t*)0x23)
#define PORTC                   (*(volatile uint8_t*)0x28)
#define DDRC                    (*(volatile uint8_t*)0x27)
#define PINC                    (*(volatile uint8_t*)0x26)
#define PORTD                   (*(volatile uint8_t*)0x2B)
#define DDRD                    (*(volatile uint8_t*)0x2A)
#define PIND                    (*(volatile uint8_t*)0x29)




#define Clock_Frequency  8000000
typedef enum {Erase_and_Write,Erase,Write} EEPROM_WRITE_MODES_t;
typedef enum {Idle,ADC_Noise_Reduction,Power_Down,Power_Save,Standby=6,External_Standby} Sleep_Modes_t;
typedef enum {NORMAL,PHASE_CORRECT,CTC,FAST_PWM,null,PHASE_CORRECT_OCRA,null1,FAST_PWM_OCRA}TCCR0A_WAVEFORM_GEN_MODE_t;


void  SET_EEPROM_MODE(EEPROM_WRITE_MODES_t mode ,void  EEPROM_Control_REG_value){
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
  }
  return EEPROM_Control_REG_value;
}
/* 
 old code for wiai x Amount_of_clock_cycles--
__attribute((always_inline)) inline void WAIT_AMOUNT_OF_CLOCK_CYCLES(int8_t Amount_of_clock_cycles){
  // caluute the clock Frequnecy 1/F = the amount time for 1 cycle
  while(Amount_of_clock_cycles--){
    __asm__ volatile ("nop");
  }
}
*/
int  EEPROM_WRITE_ENABLE(){
  // consider a while but it  be nice  to not have to  have in a loop
  // Wait until EEPE becomes zero.
  if ((EEPROM_Control_Read_REG&0x2)==0x0){
    // Wait until SELFPRGEN in SPMCSR becomes zero.
    if ((SPMCSR_read&0x0)==0){
      // Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR.
      EEPROM_Control_REG=0x6;
      EEPROM_Control_REG =0x2;
      return 0;
    }

  }
  else {
    return -1;   
  }
}
uint8_t EEPROM_READ(uint16_t* Adreess){
  // wait for completion of  previous write 
  while (EEPROM_Control_Read_REG&0x02);// wait for  the control reg to be x005E

  EEARL_REG=(uint8_t)(Address &0xFF);  
  EEPROM_Control_Read_REG|=0x01;// eeprom read enable 
  return EEDR_R;
} 
void EEPROM_WRITE(void* Address,void ucData){
  EEPROM_WRITE_ENABLE();
  EEARL_REG=Address;
  EEPROM_Data_REG=ucData;
}

int SLEEP_MODE_SELECT(Sleep_Modes_t mode){
  switch (mode){
    case Idle:break;
    case ADC_Noise_Reduction:
      SMCR |=0x2;
      break;
    case Power_Down:
      SMCR |=0x3;
      break;
    case Power_Save
      SMCR|=0x4;
      break;
    case Standby:
      SMCR=0x7;
      break;
    case External_Standby:
      SMCR=0x8;
      break;
    default:
      return -1;
  }
  return 0;
}
void Move_interputs(void){
  MCUCR =0x1;
  MCUCR|=0x2;
}
int  TCCR0A_MOODE_SET(TCCR0A_WAVEFORM_GEN_MODE_t mode,int OP){
  TCCR0A=mode;
  // make sure we clear the op modes before anything happens
  TCCR0A &=~(0b11<<6);
  switch (mode){
    case NORMAL:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
        case 1:
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A|=(0b10<<6);
          break;
        case 4:
          TCCR0A|=(0b11<<6);
          break;
        default:
          return -1;
      }
      break;
    case PHASE_CORRECT:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
        case 1:
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A |=(0b10<<6);
          break;
        case 4:
          TCCR0A |=(0b11<<6);
          break;
        default:
          return -1;
      }
      break;
    case CTC:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
        case 1:
          // we are assumeing  that it normal port op ill look into 
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A |=(0b10<<6);
          break;
        case 4:
          TCCR0A |=(0b11<<6);
          break;
        default:
         return -1;
      }
      break;
    case FAST_PWM:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
          case 1:
          // setting WGM02 to 1 to toggle compare match 
          TCCR0B |=0x8; 
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A |=(0b10<<6);
          break;
        case 4:
          TCCR0A |=(0b11<<6);
          break;
        default:
         return -1;
      }
      break;
    case PHASE_CORRECT_OCRA:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
        case 1:
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A |=(0b10<<6);
          break;
        case 4:
          TCCR0A |=(0b11<<6);
          break;
        default:
          return -1;
      }
      break;
    case FAST_PWM_OCRA:
      switch(OP){
        case 0:
          TCCR0A &=~(0b11<<6);
          break;
        case 1:
          TCCR0A |=(0b01<<6);
          break ;
        case 2:
          TCCR0A |=(0b10<<6);
          break;
        case 4:
          TCCR0A |=(0b11<<6);
          break;
        default:
          return -1;
      }
      break;
    
    default:
      return -1;
  }
  return 0;
}
void AVR_DRIVER_INIT(){
  // set Stack pointer high to the highest 
  SPH_REG = 0x08;
  // set Stack pointer low to the highest 
  SPL_REG =0xFF;
  // set up the adc 
  CLKPR =0x80;
  CLKPR =0x00;
  // sleep mode set
  SMCR=0x1;
  SLEEP_MODE_SELECT(Idle);

  // set the global interupt enable to be on.
  SREG_REG= 0x80;
  // once loaded set TCCR0B to clkio no prescaling 
  TCCR0B =0x1;
  TCCR0A_MOODE_SET(FAST_PWM,1)
  // set the  OCROB interupt as  bit 4 
  OCROA |=0x10; 
  // set the timer interupt mask 
  // enable the interupt
  TIMSKO =0x2;
  // set the match flag to OCROA
    
 }
#endif 
