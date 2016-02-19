/*
 * // Refer to: 
 * 		Shutdown Sequence using SIGINT: http://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
*/


#include "ShutDown.h"

void ShutDown_Init(void)
{
	//void SHUTDOWN_Init_Signal_Function(void);
	void signal_callback_handler(int);			
}

void ShutDown_Init_Signal_Function(void)
{
	//Two inputs: 
	//	First = Signal Value or input that we want. In this case we want SIGINT -> "Shift + c" 
	//  Second = A pointer to a signal handler which is a fucntion that calls the shutdown procedures (Signal_Callback_handler) 
	signal(SIGINT, signal_callback_handler);
}

void signal_callback_handler(int signum)
{
   printf("\nCaught signal SIGINT (%d)\n",signum);
 /*  
   bcm2835_gpio_write(LED1, LOW);
   bcm2835_gpio_write(LED2, LOW);
   bcm2835_gpio_write(LED3, LOW);
   bcm2835_gpio_write(LED4, LOW);
   bcm2835_gpio_write(LED5, LOW);
   bcm2835_gpio_write(LED6, LOW);
   bcm2835_gpio_write(LED7, LOW);
   bcm2835_gpio_write(LED8, LOW);
   bcm2835_gpio_write(ACRELAY, LOW);
   bcm2835_gpio_write(RELAY1, LOW);
*/
   bcm2835_gpio_clr_multi(1 << RPI_V2_GPIO_P1_12);
   bcm2835_spi_end();
   bcm2835_close();
   exit(signum);
}

/*
 * EXAMPLE:
 * 
 * 
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("received SIGINT\n");
}

int main(void)
{
  if (signal(SIGINT, sig_handler) == SIG_ERR)
  printf("\ncan't catch SIGINT\n");
  // A long long wait so that we can easily issue a signal to this process
  while(1) 
    sleep(1);
  return 0;
}
* 
* 
*/

