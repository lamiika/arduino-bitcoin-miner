# Baremetal Arduino bitcoin miner

Practice for my [FPGA bitcoin miner project.](https://github.com/lamiika/fpga-bitcoin-miner)

## Configuring the development environment

### Running just C code on the computer:
* comment out things that give errors like line 1 #include <avr/io.h>
* gcc miner.c -o miner && ./miner

### Arduino baremetal setup:

#### On WSL2 Ubuntu
* sudo apt install avr-libc avrdude binutils-avr gcc-avr
* dmesg | grep tty
* replace ttyUSB0 in Makefile with your usb port
* make (should compile and upload to Arduino)

#### Might be required to make Arduino visible on WSL2, do on Windows PowerShell (administrator)
* winget install usbipd
* usbipd list
* look for USB Serial Converter and BUSID is 2-3 in my case
* usbipd attach --wsl --busid 2-3
* if this fails do "usbipd bind --busid 2-3 --force" (and redo last command)