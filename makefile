CC=avr-gcc
LD=avr-ld
OBJCPY=avr-objcopy
MMCU=atmega8515
CFLAGS=-Wall -Os -I. -I/opt/avr8-gnu-toolchain-linux_x86_64/avr/include/
SOURCEDIR=Source
BUILDDIR =Build

SRC=$(wildcard *.c)
LIB=$(wildcard *.h)

all: main.out main.hex

main.out: $(SRC)
	$(CC) -mmcu=$(MMCU) -o $@ $^ $(CFLAGS) 

main.hex: main.out
	$(OBJCPY) -j .text -j .data -O ihex $< $@

avrdude: main.hex
	avrdude -c avrispmkII -p atmega8515 -P usb -U main.hex

clean:
	rm *.hex *.out
