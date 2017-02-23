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
#define LED1 RPI_V2_GPIO_P1_07
#define LED2 RPI_V2_GPIO_P1_11
#define LED3 RPI_V2_GPIO_P1_13
#define LED4 RPI_V2_GPIO_P1_15

//#define CS1 RPI_V2_GPIO_P1_31
//#define CS2 RPI_V2_GPIO_P1_33
//#define CS3 RPI_V2_GPIO_P1_35
//#define CS4 RPI_V2_GPIO_P1_37

int main(int argc, char **argv)
{
	// If you call this, it will not actually access the GPIO
	// Use for testing
//	bcm2835_set_debug(1);

	if (!bcm2835_init())
		return 1;

	// Set the pin to be an output
	bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED3, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED4, BCM2835_GPIO_FSEL_OUTP);
	
	//bcm2835_gpio_fsel(CS1, BCM2835_GPIO_FSEL_INPT);
	//bcm2835_gpio_fsel(CS2, BCM2835_GPIO_FSEL_INPT);
	//bcm2835_gpio_fsel(CS3, BCM2835_GPIO_FSEL_INPT);
	//bcm2835_gpio_fsel(CS4, BCM2835_GPIO_FSEL_INPT);
	
	while(1)
	{	

		bcm2835_gpio_write(LED1, HIGH);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED1, LOW);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED2, HIGH);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED2, LOW);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED3, HIGH);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED3, LOW);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED4, HIGH);
		bcm2835_delay(500);
		bcm2835_gpio_write(LED4, LOW);
		bcm2835_delay(2000);


	}
	bcm2835_close();	
	return 0;
}

