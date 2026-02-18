# progression
1. cossinewave into  intel hex format  ***8 bit  ***
2. vaildate the address in the hex file  
3. EEPROM  write the intel hex into the EEPROM (arvdude ?)
4. Implement the Phase accumoltor (using arduion clock )
5. Implement a DFF Ideally (on board )
6. access the memories of  my EEPROM with phase accumoltor
7. Access the  boards DAC (PWM)
8. on baord Filter 
## Critical 3 AM Hardware Notes:

1. Stack Pointer: Set SPH = 0x08 and SPL = 0xFF in AVR_DRIVER_INIT.

2. Clock: Write 0x80 then 0x00 to CLKPR to run at the full 8MHz.

3. Memory: Keep the if (count < BUFFER_SIZE) check in your loader to prevent the data from spilling into your Phase Accumulator variables.
