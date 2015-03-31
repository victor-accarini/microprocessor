CC=avr-gcc
LD=avr-ld
OBJCPY=avr-objcopy
MMCU=atmega8515
CFLAGS=-Wall -I.
SOURCEDIR= Source
BUILDDIR = Build
OBJ= main.o util.o mem.o uart.o functions.o
DEPS = util.h mem.h uart.h fuctions.h

all: main main.hex avrdude

main.out: main.c functions.c util.c mem.c uart.c
	$(CC) -mmcu=$(MMCU) -o $@ $^ $(CFLAGS) 

main.hex: main.out
	$(OBJCPY) -j .text -j .data -O ihex $< $@

avrdude: main.hex
	avrdude -c avrispmkII -p atmega8515 -P usb -U main.hex
