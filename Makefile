generate_sample =gcc samplegenerator.c -std=c99 -Wall -Werror -fsanitize=address -o samplegen -lm 
dds_driver:
	# 1. compile the Hal source 
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -c avr.c -o avr.o
	# 2. compile main 
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -c main.c -o main.o
	# 3. link the above 
	avr-gcc -mmcu=atmega328p main.o avr.o -o main.elf 
	# 4, convert main.elf into main.hex 
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex 
	# 4. create hex file named sinewave.hex 
	$(generate_sample)&&./samplegen

memmap:
	glow  EEPROM_MEMORY_MAP.md 

