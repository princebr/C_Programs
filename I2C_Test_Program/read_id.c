// read_id.c
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
#define PIN RPI_GPIO_P1_11
#define MAX_LEN 32

int i;
char buf[MAX_LEN];
uint8_t data;
uint32_t len = 0;
char addr = 

int main(int argc, char **argv)
{	

	if (!bcm2835_init())
		return 1;

	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0xBF);  // 0xBF Read, 0xBE Write, 0xBC Who_Am_I
	
//	for (i=0; i<MAX_LEN; i++) buf[i] = 'n';
//    data = bcm2835_i2c_read(buf, len);
//    printf("Read Result = %d\n", data);   
	
	uint8_t data = bcm2835_i2c_read_register_rs(0x0F, buf, 1);
	
//	uint8_t addr = bcm2835_i2c_read(0x0F, 1);				// Who_Am_I address

	
	while(1)
	{	
		// Set the pin to be an output
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
		
		// Blink
		bcm2835_gpio_write(PIN, HIGH);
		
		// Wait a bit
		bcm2835_delay(500);
		
		// Turn it off
		bcm2835_gpio_write(PIN, LOW);
		
		// Wait a bit
		bcm2835_delay(500);
	}
	bcm2835_close();	
	return 0;
}

