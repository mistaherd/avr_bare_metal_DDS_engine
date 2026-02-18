# Introduction
In this small document will be the Memory map for this project :
# EEPROM Memory Map: Sine Wave LUT
| Address | Name          | type    | Descripton |
| :-----: | :-----------: | :-----: | :--------: |
| 0x0000  | start address | uint8_t | first 17 bytes of the sinewave array |
| 0x0010  | next address  | .....   | next 17 bytes of data |
| 0x0020  | .........     | .....   | .....      |
| 0x0030 ...etc | .........     | .....   | .....      |
| 0x00F0  | last address  | ......  |last 17 bytes of the sinewave array |
 
