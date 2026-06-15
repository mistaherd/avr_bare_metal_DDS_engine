MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Werror
CFLAGS_DEBUG =-mmcu=$(MCU) -DF_CPU=$(F_CPU) -O0 -g -Wall
all :sample dds_driver
sample:arena.h 
	gcc samplegenerator.c -std=c99 -Wall -Werror -fsanitize=address -o samplegen -lm 
	./samplegen
dds_driver: main.c avr.h
	
	# 1. compile the Hal source
	
	$(CC) $(CFLAGS)  main.c -o main.elf
	# 2. convert main.elf into main.hex 
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex 
flash: main.hex sample
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i -U eprom:w:Sinewave.hex:i
debug_sample:
	gcc samplegenerator.c -std=c99 -Wall -Werror -fsanitize=address -g  -o samplegen -lm 
debug_hal:
	$(CC) $(CFLAGS_DEBUG) main.c -o main.elf 
memmap:
	glow  EEPROM_MEMORY_MAP.md 

clean:	
	rm -f *.o *.elf *.hex samplegen
