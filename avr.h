#ifndef NO_STDINT
  #include <stdint.h>
#else
  typedef unsigned char uint8_t;
#endif
#ifdef AVR_DRIVER_IMPLEMENTATION
#define OSCCAL                  (*(volatile uint8_t*)0x0066)
#define CLKPR                   (*(volatile uint8_t*)0x0061)
#define SMCR                    (*(volatile uint8_t*)0x0053)
#define PRR                     (*(volatile uint8_t*)0x0064)
#define WDTCSR                  (*(volatile uint8_t*)0x0060)
#define MCUCR                   (*(volatile uint8_t*)0x0055)
#define EICRA                   (*(volatile uint8_t*)0x0069)
#define EIMSK                   (*(volatile uint8_t*)0x003D)
#define EIFR                    (*(volatile uint8_t*)0x003C)
#define PCICR                   (*(volatile uint8_t*)0x0068)
#define PCIFR                   (*(volatile uint8_t*)0x003B)
#define PCMSK2                  (*(volatile uint8_t*)0x006D)
#define PCMSK1                  (*(volatile uint8_t*)0x006C)
#define PCMSK0                  (*(volatile uint8_t*)0x006B)
#define PORTB                   (*(volatile uint8_t*)0x0025)
#define DDRB                    (*(volatile uint8_t*)0x0024)
#define PINB                    (*(volatile uint8_t*)0x0023)
#define PORTC                   (*(volatile uint8_t*)0x0028)
#define DDRC                    (*(volatile uint8_t*)0x0027)
#define PINC                    (*(volatile uint8_t*)0x0026)
#define PORTD                   (*(volatile uint8_t*)0x002B)
#define DDRD                    (*(volatile uint8_t*)0x002A)
#define PIND                    (*(volatile uint8_t*)0x0029)
#define TCCR0A                  (*(volatile uint8_t*)0x0044) // mode 
#define TCCR0B                  (*(volatile uint8_t*)0x0045) // control clock divider
#define TCNTO                   (*(volatile uint8_t*)0x0046)
#define OCROA                   (*(volatile uint8_t*)0x0047)
#define OCROB                   (*(volatile uint8_t*)0x0048)
#define TIMSKO                  (*(volatile uint8_t*)0x006E)
#define TIFRO                   (*(volatile uint8_t*)0x0035)
#define SPMCS                   (*(volatile uint8_t*)0x0057)
#define SREG_REG                (*(volatile uint8_t*)0x005F)// we write to  to as  value
#define SPH_REG                 (*(volatile uint8_t*)0x005E)
#define SPL_REG                 (*(volatile uint8_t*)0x005D)
#define EEARL_REG               (*(volatile uint8_t*)0x0041)
#define EEDR_W                  (*(volatile uint8_t*)0x0040)
#define EEDR_R                  (*(volatile uint8_t*)0x0020)// use for writeing datat to be store at 0x8 per 
#define EEPROM_Control_REG      (*(volatile uint8_t*)0x003F)
#define EEPROM_Control_Read_REG (*(volatile uint8_t*)0x001F)
#define SPMCSR_read             (*(volatile uint8_t*)0x0037)
#define GPIOR2                  (*(volatile uint8_t*)0x004B)
#define GPIOR1                  (*(volatile uint8_t*)0x004A)
#define GPIOR0                  (*(volatile uint8_t*)0x003E)
#define CLKPR                   (*(volatile uint8_t*)0x0061)
#define SMCR                    (*(volatile uint8_t*)0x0053)






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

__attribute((always_inline)) inline void WAIT_AMOUNT_OF_CLOCK_CYCLES(int8_t Amount_of_clock_cycles){
  // caluute the clock Frequnecy 1/F = the amount time for 1 cycle
  while(Amount_of_clock_cycles--){
    __asm__ volatile ("nop");
  }
}
int  EEPROM_WRITE_ENABLE(){
  // consider a while but it  be nice  to not have to  have in a loop
  // Wait until EEPE becomes zero.
  if ((EEPROM_Control_Read_REG&0x2)==0x0){
    // Wait until SELFPRGEN in SPMCSR becomes zero.
    if ((SPMCSR_read&0x0)==0){
      // Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR.
      EEPROM_Control_REG=0x6;

      // Within four clock cycles after setting EEMPE, write a logical one to EEPE.
      __asm__ volatile (
        ".rept 4\n\n\t"
        "nop\n\t"
        ".endr"
      );
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
          break return -1:
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
          break return -1:
      }
      break;
    case CTC:
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
          break return -1:
      }
      break;
    case FAST_PWM:
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
          break return -1:
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
          break return -1:
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
          break return -1:
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
}
#endif 
