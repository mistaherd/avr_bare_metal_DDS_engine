// base addr =0x0000
#define OSCCAL  (*(volatile uint8_t*)0x0066)
#define CLKPR   (*(volatile uint8_t*)0x0061)
#define SMCR    (*(volatile uint8_t*)0x0033)
#define PRR     (*(volatile uint8_t*)0x0064)
#define MCUCR   (*(volatile uint8_t*)0x0035)
#define WDTCSR  (*(volatile uint8_t*)0x0060)
#define MCUCR   (*(volatile uint8_t*)0x0055)
#define EICRA   (*(volatile uint8_t*)0x0069)
#define EIMSK   (*(volatile uint8_t*)0x003D)
#define EIFR    (*(volatile uint8_t*)0x003C)
#define PCICR   (*(volatile uint8_t*)0x0068)
#define PCIFR   (*(volatile uint8_t*)0x003B)
#define PCMSK2  (*(volatile uint8_t*)0x006D)
#define PCMSK1  (*(volatile uint8_t*)0x006C)
#define PCMSK0  (*(volatile uint8_t*)0x006B)
#define PORTB   (*(volatile uint8_t*)0x0025)
#define DDRB    (*(volatile uint8_t*)0x0024)
#define PINB    (*(volatile uint8_t*)0x0023)
#define PORTC   (*(volatile uint8_t*)0x0028)
#define DDRC    (*(volatile uint8_t*)0x0027)
#define PINC    (*(volatile uint8_t*)0x0026)
#define PORTD   (*(volatile uint8_t*)0x002B)
#define DDRD    (*(volatile uint8_t*)0x002A)
#define PIND    (*(volatile uint8_t*)0x0029)
#define TCCR0A  (*(volatile uint8_t*)0x0044)
#define TCCR0B  (*(volatile uint8_t*)0x0045)
#define TCNTO   (*(volatile uint8_t*)0x0046)
#define OCROA   (*(volatile uint8_t*)0x0047)
#define OCROB   (*(volatile uint8_t*)0x0048)
#define TIMSKO  (*(volatile uint8_t*)0x006E)
#define TIFRO   (*(volatile uint8_t*)0x0035)


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
