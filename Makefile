default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o miner.o miner.c
	avr-gcc -o miner.bin miner.o
	avr-objcopy -O ihex -R .eeprom miner.bin miner.hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB1 -b 115200 -U flash:w:miner.hex