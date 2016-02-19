/*! PN532_Proto.h
 *	C library for the PN532 Written for raspberry Pi Model 2 B+ or whaterver it was called.
 *  Adapted from the pn532.h written by Adafruit Industries
 * 	
 *  Author: Ivan
*/

#ifndef PN532_PROTO_H
#define PN532_PROTO_H

#include <stdint.h>
#include <signal.h>                          // Signals library
#include <stdlib.h>
#include <unistd.h>								
#include <stdio.h> 
#include <string.h>

// #include <bcm2835.h>						// C libraries for Raspberry Pi version 1 & 2
#include "bcm2835.h"
#include "SPI.h"

#define PN532_PREAMBLE 0x00
#define PN532_STARTCODE1 0x00
#define PN532_STARTCODE2 0xFF
#define PN532_POSTAMBLE 0x00
 
#define PN532_HOSTTOPN532 0xD4
 
//#define PN532_FIRMWAREVERSION     0x02
#define PN532_FIRMWAREVERSION     0x02
#define PN532_GETGENERALSTATUS    0x04
#define PN532_SAMCONFIGURATION    0x14
#define PN532_INLISTPASSIVETARGET 0x4A
#define PN532_INDATAEXCHANGE      0x40
#define PN532_INJUMPFORDEP        0x56     
#define PN532_TGINITASTARGET      0x8C
#define PN532_TGGETDATA           0x86
#define PN532_TGSETDATA           0x8E
 
#define PN532_WAKEUP              0x55
#define PN532_SPI_STATREAD        0x02
#define PN532_SPI_DATAWRITE       0x01
#define PN532_SPI_DATAREAD        0x03
#define PN532_SPI_READY           0x01
 
#define PN532_MIFARE_ISO14443A 0x0
 
#define KEY_A   1
#define KEY_B   2



// Setup SPI settings
uint8_t PN532_Begin(void);

uint8_t PN532_sendCommandCheckAck(uint8_t *cmd, uint8_t cmd_len, uint16_t timeout);

void PN532_writeCommand(uint8_t buf[], uint8_t cmdlen);

uint8_t PN532_SPI_ReadStatus (void);

uint8_t PN532_SPI_Read(void);

uint8_t PN532_GetFirmwareVersion(void);

void PN532_SPI_Write(uint8_t data);

uint8_t PN532_WaitReady(uint16_t timeout);

uint8_t PN532_IsReady(void);

uint8_t PN532_Read(uint8_t); 

uint8_t	PN532_ReadAck(void);

uint8_t	PN532_SPI_Read_N_Write(uint8_t inputCommand);


#endif
