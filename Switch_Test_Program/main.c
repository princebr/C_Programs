// blink.c
//
// Example program for bcm2835 library
// 
// After installing bcm2835, you can build this
// with something like:
// gcc -o blink blink.c -l bcm2835
// sudo ./blink
//
// Or you gan test it before installing with:
// gcc -o blink -I ../../serc ../../src/bcm2835.c blink.c
// sudo ./blink
//

#include <bcm2835.h>
#include <stdio.h>

// Blinks on RPi Plug P1 pin 11 (gpio pin 17)
//#define PIN RPI_GPIO_P1_11
//#define PIN RPI_GPIO_P1_07
#define SW RPI_GPIO_P1_11

int main(int argc, char **argv)
{
	// If you call this, it will not actually access the GPIO
	// Use for testing
//	bcm2835_set_debug(1);

	if (!bcm2835_init())
		return 1;
	
	while(1)
	{	
		// Set the pin to be an output
		//bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
		
		// Set pullup
		bcm2835_gpio_pud(SW);
		
		
		if (!bcm2835_gpio_lev(PIN))
		{
		
		printf ("low");
		
		// Blink
		//bcm2835_gpio_write(PIN, HIGH);
		
		}
		
		// Wait a bit
		//bcm2835_delay(100);
		
		else
		{
		printf ("high");
		
		// Turn it off
		//bcm2835_gpio_write(PIN, LOW);
		
		}
		
		// Wait a bit
		//bcm2835_delay(100);
	}
	bcm2835_close();	
	return 0;
}

