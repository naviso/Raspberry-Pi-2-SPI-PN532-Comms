/*! PN532_Proto.c
 *	C library for the PN532 Written for raspberry Pi Model 2 B+ or whaterver it was called.
 *  Adapted from the pn532.cpp written by Adafruit Industries
 * 	
 *  Author: Ivan
*/

#include "PN532_Proto.h"

#define DELAY_2_MS 2	
#define DELAY_2000_US 2000				
#define TIMEOUT_PERIOD_BASE  1000
 
#define PN532_PACK_BUFF_SIZE 64
uint8_t PN532_packetbuffer[PN532_PACK_BUFF_SIZE];

uint8_t pn532ack[] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};

uint8_t pn532response_firmwarevers[] = {0x00, 0xFF, 0x06, 0xFA, 0xD5, 0x03};

//! STAGE 00  + STAGE 01
uint8_t PN532_Begin(void)
{
	uint8_t boolValue;
	uint8_t junkData = 0x00;
	
	SPI_Begin();																// Call SPI initialisation function to start raspberry pi's SPI ports
		
	PN532_packetbuffer[0] = PN532_FIRMWAREVERSION;								// Not exactly sure why we have to send a dummy command to get synced up

//Testing initial write   
//	bcm2835_spi_writenb(&junkData, 1);

	bcm2835_spi_slave_clear_fifo_prototype();									// Clear Rx And Tx FIFOs buy sending "BCM2835_SPI0_CS_CLEAR"
    bcm2835_spi_Slave_Open_prototype();											// Make Raspbeery pi Slave Select Line active
	
	bcm2835_delay(1000);														// No idea why it has to be so long

//! STAGE 02	
	boolValue = PN532_sendCommandCheckAck(PN532_packetbuffer, 1, TIMEOUT_PERIOD_BASE);   
	
//	bcm2835_spi_Slave_Close_prototype();	// Make Raspbeery pi Slave Select Line in-active
	
	printf("\nBoolValue %02X\n", boolValue);
	
	return boolValue;
}

uint8_t PN532_GetFirmwareVersion(void)
{		
	
	uint32_t response;
	uint8_t _usingSPI = 1;
	
	PN532_packetbuffer[0] = PN532_FIRMWAREVERSION;

	printf("\nHerp\n");
	if (! PN532_sendCommandCheckAck(PN532_packetbuffer, 1, TIMEOUT_PERIOD_BASE) ) {
		return 0;
	}
	printf("Derp");

	  
}

uint8_t PN532_sendCommandCheckAck(uint8_t *cmd, uint8_t cmd_len, uint16_t timeout)
{
	uint8_t tempVal;
	uint8_t	x;
	
	PN532_writeCommand(cmd, cmd_len);									// Write Command
	
	// Wait for chip to say it's ready!
	
	bcm2835_delay(5);
	
	if ( !PN532_WaitReady(TIMEOUT_PERIOD_BASE) )						// Wait for the chip to say ready
	{
		printf("\nFunction PN532_sendCommandCheckAck() Problem\n");
		return 0;
	}

	return 1;
}

void PN532_writeCommand(uint8_t buf[], uint8_t cmdlen)
{	
	uint8_t checksum;
	uint8_t counter;

    cmdlen++;
    
    
    printf(("\nSending command "));

    bcm2835_spi_slave_clear_fifo_prototype();
    bcm2835_spi_Slave_Open_prototype();							        // Slave Select line active
    bcm2835_delay(DELAY_2_MS);     										// or whatever the delay is for waking up the board
  
	PN532_SPI_Write(PN532_SPI_DATAWRITE);
    checksum = PN532_PREAMBLE + PN532_PREAMBLE + PN532_STARTCODE2;
    
    PN532_SPI_Write(PN532_PREAMBLE);
    PN532_SPI_Write(PN532_STARTCODE1);
    PN532_SPI_Write(PN532_STARTCODE2);

    PN532_SPI_Write(cmdlen);
    PN532_SPI_Write(~cmdlen + 1);   									

    PN532_SPI_Write(PN532_HOSTTOPN532);
    checksum += PN532_HOSTTOPN532;

//bcm2835_spi_slave_clear_fifo_prototype();
    for (counter = 0; counter < cmdlen - 1; counter++) 
    {    
        PN532_SPI_Write(buf[counter]);
        checksum += buf[counter];  
    }
    //printf("\n");

    PN532_SPI_Write(~checksum);
    PN532_SPI_Write(PN532_POSTAMBLE);
    
    bcm2835_spi_Slave_Close_prototype();								// Slave Select line in-active

//#ifdef PrintedCommands
	printf("\n Preamble 00:\n", PN532_PREAMBLE);
	printf("startcode 1: %02X\n", PN532_PREAMBLE);
	printf("startcode 2: %02X\n", PN532_STARTCODE2);
	printf("CMD len: %02X\n", cmdlen);
	printf("CMD LCS = (len + ~len + 1): %02X\n", ~cmdlen + 1);
	printf("Host to PN532 CMD 2: %02X\n", PN532_HOSTTOPN532);
	printf("\nChecksum: %02X\nChecksum ~: %02X\n", checksum, ~checksum);
	printf("\nPostamble: %02X\n", PN532_POSTAMBLE);
	
//#endif

}


uint8_t PN532_SPI_ReadStatus (void)
{
	uint8_t statusRead = 12;
	
    // Turn on CS line 
	bcm2835_spi_Slave_Open_prototype();				// Set slave line low to begin communications
	bcm2835_delay(DELAY_2_MS);
	
	bcm2835_spi_transfer_prototype(PN532_SPI_STATREAD);
	
//    statusRead = PN532_SPI_read();

	bcm2835_spi_Slave_Close_prototype();
	
	return statusRead;
}

// Returns the 8 bit value that was read from the SPI bus

uint8_t PN532_SPI_Read(void)
{
	// return bcm2835_spi_read_prototype();							// send some junk data
	return bcm2835_spi_transfer_prototype(0x00);
}

void PN532_SPI_Write(uint8_t data)	//! Recheck if 8 bytes only before closing lines again
{
	//bcm2835_delay(5);
	
	bcm2835_spi_write_prototype(data);									// Writes 1 byte to slave
	//bcm2835_spi_transfer(data);											
	//bcm2835_spi_writenb(&data, 1);
}

uint8_t PN532_WaitReady(uint16_t timeout)  								// Default timeout is 1000 ms 
{
	uint16_t timer = 0;
	
	while( !PN532_IsReady() )    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	{
		if (timeout != 0)
		{
			timer +=10;
		}
		if (timer > timeout)
		{
			printf("\nTimeout Period Expired: PN532_WaitReady -> Function\n");
			return 0;
		}
		
		bcm2835_delay(10);
	}
	
	return 1;
	
}

/*
	Brief Return true if the PN532 is ready with a response
*/
uint8_t PN532_IsReady(void) // Missing something 
{
	uint8_t readValFromSPI;
	uint8_t length = 1;
	uint8_t transValToS[]  = {PN532_SPI_STATREAD};
	uint32_t readValFromS[] = {0x0A};
	
	bcm2835_spi_slave_clear_fifo_prototype();
	bcm2835_spi_Slave_Open_prototype();									// Write Low to Slave Select
	bcm2835_delay(DELAY_2_MS);
		
//	readValFromSPI = PN532_SPI_Read_N_Write(PN532_SPI_STATREAD); 		// Write and read response byte sent
	PN532_SPI_Write(PN532_SPI_STATREAD);
	readValFromSPI = PN532_SPI_Read();

	
	bcm2835_spi_Slave_Close_prototype();								// Write Low to Slave Select
	
//	readValFromSPI = bcm2835_spi_transfer(PN532_SPI_STATREAD);
	
	if (readValFromSPI == PN532_SPI_STATREAD)
	{
	    printf("Function PN532_isReady return val %02X = const: %04X\n", PN532_SPI_STATREAD, readValFromSPI);				// Delete Later
		return 1;
	}
	return 0;
}
uint8_t	PN532_ReadAck(void)
{
	
}

/* Writes (and reads) a single byte to SPI Slave Device*/
uint8_t PN532_SPI_Read_N_Write(uint8_t inputCommand)
{
	return bcm2835_spi_transfer_prototype(inputCommand);
}
