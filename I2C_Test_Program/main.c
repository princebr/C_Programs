// main.c
//
// Test program for bcm2835 library
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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LED1 RPI_V2_GPIO_P1_07
#define LED2 RPI_V2_GPIO_P1_11
#define LED3 RPI_V2_GPIO_P1_13
#define LED4 RPI_V2_GPIO_P1_15

#define SW1 RPI_V2_GPIO_P1_29
#define SW2 RPI_V2_GPIO_P1_31
#define SW3 RPI_V2_GPIO_P1_33
#define SW4 RPI_V2_GPIO_P1_35
#define SW5 RPI_V2_GPIO_P1_37

#define MODE_READ 0
#define MODE_WRITE 1
#define MAX_LEN 32

#define MODE1 0x00
#define MODE2 0x01
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define LED2_ON_L 0x0E
#define ALL_LED_ON 0xFA
#define ALL_LED_OFF 0xFC
#define PRE_SCALE 0xFE

char wbuf[MAX_LEN];
char rbuf[MAX_LEN];


char mode_msg[] = {MODE1, 0x80};//01};		// MODE1 => 0x01, reset chip
char autoinc_msg[] = {MODE1, 0xA1}; 	// MODE1 => 0xA1, auto-increment
char cfg_msg[] = {MODE2, 0x04}; 		// MODE2 => 0x04, hardware configuration
char led0_on[] = {LED0_ON_L, 0x00, 0x00, 0x00, 0x00};

// TEST Buffers
char led2_on[] = {LED2_ON_L, 0x00, 0x00, 0x10, 0x00};
char led2_off[] = {LED2_ON_L, 0x00, 0x00, 0x00, 0x00};
//--------------

char all_on[] = {ALL_LED_ON, 0xBB};
char all_off[] = {ALL_LED_OFF, 0x00};


uint8_t slave_address = 0x42;
uint8_t data;

int main(int argc, char **argv)
{

	/*--------------- Initialize Hardware -----------------*/

	if (!bcm2835_init())
		return 1;
	
	bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED3, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(LED4, BCM2835_GPIO_FSEL_OUTP);
	
	bcm2835_gpio_fsel(SW1, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(SW2, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(SW3, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(SW4, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(SW5, BCM2835_GPIO_FSEL_INPT);
	
	bcm2835_i2c_setSlaveAddress(slave_address);
	bcm2835_i2c_begin();

	/*--------------- Initialize Peripherals --------------*/

	data = bcm2835_i2c_write(autoinc_msg, 2);
	printf("Write Result (Autoinc) = %d\n", data); 
	delay(1);
	data = bcm2835_i2c_write(cfg_msg, 2);
	//printf("Write Result (Config) = %d\n", data); 
	delay(1);
	
	/*------------------- Main Routine --------------------*/
	
	
	char i = 20;
				
	while (1)
	{
		for (i=0; i<256; i++)
		{
			led0_on[3] = i;

			data = bcm2835_i2c_write(led0_on, 5);
			printf("Write Result (up) = %d\n", i);
			delay(10);
			
			if (!bcm2835_gpio_lev(SW2)) 
			{
				bcm2835_i2c_write(led2_on, 5);
				bcm2835_gpio_write(LED1, HIGH);
				printf("ATTD ON");
				//delay(200);
			}
			else
			{
				bcm2835_i2c_write(led2_off, 5);
				bcm2835_gpio_write(LED1, LOW);
				printf("ATTD OFF");
				//delay(200);
			}
		}
		/*
		for (k=255; k>0; k--)
		{
			led2_on[3] = k;

			data = bcm2835_i2c_write(led2_on, 5);
			printf("Write Result (down) = %d\n", k);
			delay(10);
		}*/
		
		delay(50);
	}
	
	bcm2835_i2c_end(); 


	bcm2835_close();	
	return 0;
}

