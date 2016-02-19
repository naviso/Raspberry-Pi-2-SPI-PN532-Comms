// File used for interfacing Pi with Ardruino

#include "SPI.h"

#define PN532_COMMAND_GETFIRMWAREVERSION    (0x02)

/*
#define PN532_PACKBUFFSIZ 64
uint8_t PN532_packetbuffer[PN532_PACKBUFFSIZ];
*/


void printing(void)
{
	//printf("Rand Value Generator: %f\r", rand() * -0.1);
}

void SPI_Begin(void)
{
	// Im Assuming this the PI is going to be the master......
	
	bcm2835_spi_begin(); 									     // Start SPI operations (See details on bcm2835 library)
	
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);	 // Is data shifted in Most Significant Bit (MSB) or Least Significant Bit (LSB) first?
	
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  // NEED TO ASK WHAT THE SETTINGS OF ARDUINO IS												

	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16384);   // SPI Clock Speed I'M ASSUMING ARDUINO IS 4MHZ CLOCK SPEED (250 / 64 = ~4 MHz)
	
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     // NEED MORE INFORMATION -> Only using 1 device........
	 
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     // NEED MORE INFORMATION -> Default setup
	

	//SPI_PN532_Setup();
	
	/*!
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    */
}

void SPI_PN532_Setup(void)
{
	
}


