#include <signal.h>  						// Shutdown Sequence using SIGINT: http://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
#include <stdlib.h>
#include <unistd.h>								

//! #include <nfc/nfc.h> Hot Garbage
//////////////////////////////////////////////

#include <stdio.h>
//#include <bcm2835.h>						// C libraries for GPIO Raspberry Pi version 1 & 2 I/O

#include "SPI.h"
#include "test.h"

#include "ShutDown.h"
#include "PN532_Proto.h"
#include "bcm2835.h"						// C libraries for GPIO Raspberry Pi version 1 & 2 I/O

#define LED_TEST RPI_V2_GPIO_P1_12		   	// Assigning LED output to pin 12?

#define INT_REQUEST RPI_V2_GPIO_P1_40   
uint16_t Test_Value = 123;

uint8_t Main_Hardware_Init(void);

/* Function Prototypes */
// void signal_callback_handler(int);          // Catches signal (e.g. ^c shutdown)
void ShutDown_Init();     

int main(int argc, char **argv)
{
	const unsigned int delay_time_ms = 250;  
	uint8_t	counter   = 0;
	uint8_t send_data = 0x23;

	uint8_t buf[] = { 0x00, 0x00, 0xFF, 0x01, 0xFE, 0xD4, 0x02, 0x2A };
	uint8_t rbuf[8];
	uint8_t loop = 1;
	
	//volatile uint32_t* paddr = bcm2835_spi0 + BCM2835_SPI0_CS/4;
	
	/* CALL THE SIGNAL HANDLER FUNCTION ON A Ctrl-C EXIT */
    // signal(SIGINT, signal_callback_handler);
	ShutDown_Init_Signal_Function();

    printf("\rINITIATOR STARTED\n");
    
	if ( Main_Hardware_Init() )
	{
		printf("SPI Initialisation has gone all wrong");	
		loop = 0;		
	}
	
	printf("\nLoop Value = %d\n", loop);	
	while (loop)
	{    
	/*
        bcm2835_spi_transfern(buf, sizeof(buf));

    */  
        //bcm2835_spi_transfern(buf, sizeof(buf));
        
        // bcm2835_spi_writenb(buf, sizeof(buf));  
        
		bcm2835_spi_transfernb(buf, rbuf, sizeof(buf)); 
		
/*
	bcm2835_delay(500);
	bcm2835_spi_Slave_Open_prototype();
	bcm2835_delay(500);
	bcm2835_spi_Slave_Close_prototype();
*/
	
/*   bcm2835_spi_Slave_Close_prototype();  
bcm2835_delay (delay_time_ms);  
   bcm2835_spi_Slave_Open_prototype();
*/  
    
    bcm2835_delay (delay_time_ms);
//bcm2835_spi_Slave_Open_prototype();

//	bcm2835_delay (delay_time_ms);

//bcm2835_spi_Slave_Close_prototype();
	
        //value = bcm2835_gpio_lev(INT_REQUEST);
        //printf("\n %d", value);
        
        // bcm2835_spi_transfer_prototype(12);
        
//bcm2835_delay (delay_time_ms);
		

printf("Read from SPI: %02X  %02X  %02X  %02X  %02X  %02X\n", rbuf[0], rbuf[1], rbuf[2], rbuf[3], rbuf[4], rbuf[5]);
		//bcm2835_delay (delay_time_ms);	
		
	}
	
//	getchar();
	//! Shutdown the GPIOs after unsuccessful finish
	{
		bcm2835_gpio_clr_multi(1 << RPI_V2_GPIO_P1_12);
		bcm2835_spi_end();
		bcm2835_close();
	}
	return 0;
}

uint8_t Main_Hardware_Init(void)
{
	uint32_t versionDataRFID;

	if ( !bcm2835_init() )
		return 1;														// return value if initialisation of bcm2835 C functions fails
	bcm2835_gpio_fsel(LED_TEST, BCM2835_GPIO_FSEL_OUTP);				// Set the registers as either input or output of the pin for LED Test Function
	bcm2835_gpio_fsel(INT_REQUEST, BCM2835_GPIO_FSEL_INPT);
	printf("\nBCM_2835 init Success\n");


    while ( !PN532_Begin() )
    {
		printf("\nInitial comms with PN532 fail\n");
		return 1;														
	}

	printf("\nPN532_Begin() Sucessl\n");

	
	printf("Begin Dummy code SPI transfer\n");
//! Current POSITION STAGE 02 START
	printf("\nStage 02 start:\n");
	
	versionDataRFID = PN532_GetFirmwareVersion();						// Getting Version data of NFC firmware

	
	if ( !versionDataRFID )
	{
		printf("\r Nope, didnt find PN532 device\n");
		while (1)
		{
			bcm2835_delay(50);
			printf("\rStop it\r");
		}
	
	}

	printf("\nSucess\n");
	return 0; 												// All good
}

