/*
 * // Refer to: 
 * 		Shutdown Sequence using SIGINT: http://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
*/

#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <stdint.h>

#include <signal.h>  // Signals library
#include <stdlib.h>
#include <unistd.h>								
#include <stdio.h> 

//#include <bcm2835.h>						// C libraries for Raspberry Pi version 1 & 2
#include "bcm2835.h"

/* FUNCTION DECLARATIONS */
void ShutDown_signal_Init(void);			// Declared as initial function protoype never to be called

void ShutDown_Init_Signal_Function(void);   // Called in main before the inifinite loop and after variable decalrations

void signal_callback_handler(int signum);	// Called when exiting once signal discovered

#endif
