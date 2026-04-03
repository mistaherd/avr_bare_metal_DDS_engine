#include <stdint.h>
#ifdef AVR_DRIVER_IMPLEMENTATION
// Global buffer for PWM filter 
// Declartions only :
extern  volatile uint8_t buffer[];
extern volatile uint16_t active_buffer_size;
extern volatile uint16_t bufferIndex;
// avr CPU core
#define SREG_REG                (*(volatile uint8_t*)0x3F)// we write to  to as  value
#define SPH_REG                 (*(volatile uint8_t*)0x3E)
#define SPL_REG                 (*(volatile uint8_t*)0x3D)
// AVR Mmemories
#define GPIOR2                  (*(volatile uint8_t*)0x2B)
#define GPIOR1                  (*(volatile uint8_t*)0x2A)
#define GPIOR0                  (*(volatile uint8_t*)0x1E)
#define EEARL_REG               (*(volatile uint8_t*)0x21)
#define EEDR                    (*(volatile uint8_t*)0x20)
#define EECR                    (*(volatile uint8_t*)0x1F)
// system Clock 
#define OSCCAL                  (*(volatile uint8_t*)0x66)
#define CLKPR                   (*(volatile uint8_t*)0x61)
// Power mangement 
#define SMCR                    (*(volatile uint8_t*)0x33)
#define PRR                     (*(volatile uint8_t*)0x64)
#define MCUCR                   (*(volatile uint8_t*)0x35)
// system control and reset
#define MCUSR                   (*(volatile uint8_t*)0x54)
#define WDTCSR                  (*(volatile uint8_t*)0x60)
// external interupt
#define EICRA                   (*(volatile uint8_t*)0x69)
#define EIMSK                   (*(volatile uint8_t*)0x1D)
#define EIFR                    (*(volatile uint8_t*)0x1C)
#define PCICR                   (*(volatile uint8_t*)0x68)
#define PCIFR                   (*(volatile uint8_t*)0x1B)
#define PCMSK2                  (*(volatile uint8_t*)0x6D)
#define PCMSK1                  (*(volatile uint8_t*)0x6C)
#define PCMSK0                  (*(volatile uint8_t*)0x6B)
// io
#define PORTB                   (*(volatile uint8_t*)0x05)
#define DDRB                    (*(volatile uint8_t*)0x04)
#define PINB                    (*(volatile uint8_t*)0x03)
#define PORTC                   (*(volatile uint8_t*)0x08)
#define DDRC                    (*(volatile uint8_t*)0x07)
#define PINC                    (*(volatile uint8_t*)0x06)
#define PORTD                   (*(volatile uint8_t*)0x0B)
#define DDRD                    (*(volatile uint8_t*)0x0A)
#define PIND                    (*(volatile uint8_t*)0x09)
// 8 bit timer counter 0 
#define TCCR0A                  (*(volatile uint8_t*)0x24) // mode 
#define TCCR0B                  (*(volatile uint8_t*)0x25) // control clock divider
#define TCNTO                   (*(volatile uint8_t*)0x26)
//#define TCNTO_READ              (*(volatile uint8_t*)0x26)
#define OCROA                   (*(volatile uint8_t*)0x27)
#define OCROB                   (*(volatile uint8_t*)0x28)
#define TIMSKO                  (*(volatile uint8_t*)0x6E)
#define TIFRO                   (*(volatile uint8_t*)0x15)
// 16 bit timer with pwm counter 1
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
#define TIFR1                   (*(volatile uint8_t*)0x16)
//  timer/counter 0 and timer/counter1 prescalers
#define GTCCR                   (*(volatile uint8_t*)0x23)
// 8 bit timer/counter 2 with pwm and asynchronous op 
#define TCCR2A                  (*(volatile uint8_t*)0xB0)
#define TCCR2B                  (*(volatile uint8_t*)0xB1)
#define TCNT2                   (*(volatile uint8_t*)0xB2)
#define OCR2A                   (*(volatile uint8_t*)0xB3)
#define OCR2B                   (*(volatile uint8_t*)0xB4)
#define TIMSK2                  (*(volatile uint8_t*)0x70)
#define TIFR2                   (*(volatile uint8_t*)0x37)
#define ASSR                    (*(volatile uint8_t*)0xB6)
//#define GTCCR
// SPI 
#define SPCR                    (*(volatile uint8_t*)0x4C)
#define SPSR                    (*(volatile uint8_t*)0x4D)
#define SPDR                    (*(volatile uint8_t*)0x4E)
// UART0 
// boot loader
#define SPMCS                   (*(volatile uint8_t*)0x57)
#define SPMCSR                  (*(volatile uint8_t*)0x37)

// set up for isr 
void __attribute__((signal,used,externally_visible)) __vector_14(void){
  OCROA=buffer[bufferIndex];
  // problem of reaching the max vaule easily 
  bufferIndex ++;
  if (bufferIndex >=active_buffer_size){
    bufferIndex=0;
  }

}

#define Clock_Frequency  8000000
typedef enum {Erase_and_Write,Erase,Write} EEPROM_WRITE_MODES_t;
typedef enum {Idle,ADC_Noise_Reduction,Power_Down,Power_Save,Standby=6,External_Standby} Sleep_Modes_t;


void  SET_EEPROM_MODE(EEPROM_WRITE_MODES_t mode){
  switch (mode){
    case Erase_and_Write:break;
    case Erase:
      EECR|= 0x10;
      break;
    case Write:
      EECR |= 0x20;
      break;
    default:
      return -1;
  }
  return;
}

int  EEPROM_WRITE_ENABLE(){
  // consider a while but it  be nice  to not have to  have in a loop
  // Wait until EEPE becomes zero.
  if ((EECR&0x2)==0x0){
    // Wait until SELFPRGEN in SPMCSR becomes zero.
    if ((SPMCSR&0x0)==0){
      // Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR.
      EECR=0x6;
      EECR=0x2;
      return 0;
    }

  }
  else {
    return -1;   
  }
}
uint8_t EEPROM_READ(uint8_t* Address){
  // wait for completion of  previous write 
  while (EECR&0x02);// wait for  the control reg to be x005E

  EEARL_REG=&Address;  
  EECR|=0x01;// eeprom read enable 
  return EEDR;
} 
void EEPROM_WRITE(void* Address,uint8_t ucData){
  EEPROM_WRITE_ENABLE();
  EEARL_REG=Address;
  EEDR=ucData;
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
    case Power_Save:
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
 
  //TCCR0A_MOODE_SET(FAST_PWM,1)
  // set mode to FAST_PWM
  TCCR0A =(0b01<<6);
  // set the mode  to FAST_PWM
  TCCR0A |=0b11;
  TCCR0B =(0x1<<3);
  // once loaded set TCCR0B to clkio no prescaling 
  TCCR0B |=0x1;
  
  // set the  OCROB interupt as  bit 4 
  //OCROA |=0x10; 
  // set the timer interupt mask 
  // enable the interupt
  TIMSKO =0x2;
  // set the match flag to OCROA
  TIFRO =0x2;
  // set the directonm of port D PD6 
  DDRD|=(1<<6);
  
 }
#endif 
