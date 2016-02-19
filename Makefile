# Variables to use rather than typing the same length 
cc = gcc
# C compiler option (c = compile)
cflags = -c
# finding libraries
# pi = -l bcm2835


all: SPI_Comms

# Listing All objects that SPI_Coms.exe need
SPI_Comms: main.o SPI.o test.o ShutDown.o PN532_Proto.o bcm2835.o
	$(cc) main.o SPI.o test.o ShutDown.o PN532_Proto.o bcm2835.o -o SPI_Comms 
	#$(pi)

# Listing object dependancies	
main.o: main.c
	$(cc) $(cflags) main.c
	
SPI.o: SPI.c
	$(cc) $(cflags) SPI.c
	
test.o: test.c
	$(cc) $(cflags) test.c

Shutdown.o: ShutDown.c
	$(cc) $(cflags) ShutDown.c

PN532_Proto.o: PN532_Proto.c
	$(cc) $(cflags) PN532_Proto.c

bcm2835.o: bcm2835.c
	$(cc) $(cflags) bcm2835.c

# Clean *o removes object files, and inserting exe name removes executable
clean:
	rm rf *o *SPI_Comms

