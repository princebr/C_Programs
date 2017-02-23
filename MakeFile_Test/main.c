// main.c
//
// Test program for bcm2835 library
// 


#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>	// Use to print out uint64_t data types
#include <functions.h>	// Place this after stdint.h for var types


int main(int argc, char **argv)
{
	/*--------------- Initialize Hardware -----------------*/

	init_bcm();

	/*--------------- Initialize Peripherals --------------*/

	init_periph();
	
	/*--------------- Set Initial Conditions --------------*/

	set_initial_conditions();
	
	// Write to all lighting features ...
	//write_RGBlighting_feature(backshellLight);
	//write_RGBlighting_feature(stowageLight);
	
	write_lighting_feature(capTTLLight);
	delay_ms(500);
	write_lighting_feature(capLAYLight);
	delay_ms(500);
	write_lighting_feature(capRLLight);
	delay_ms(500);
	write_lighting_feature(capDNDWhiteLight);
	//delay_ms(500);
	//write_lighting_feature(capDNDRedLight);
	delay_ms(500);
	write_lighting_feature(capATTDWhiteLight);
	//delay_ms(500);
	//write_lighting_feature(capATTDBlueLight);
	delay_ms(500);
	readingLight2.pwmRaw = 0;
	write_lighting_feature(readingLight2);
	
	
	/*------------------- Main Routine --------------------*/
	
	uint8_t read_buf[2];
	bcm2835_i2c_setSlaveAddress(0x76);
	bcm2835_i2c_read_register_rs(0xD0, read_buf, 1);
	print("%d\n", read_buf[0]); 
	
	
	uint8_t i;
	
	/*
	for (i=0; i<100; i++){
		backshellLight.pwmRaw_B = i;
		backshellLight.pwmRaw_G = 100-i;
		write_RGBlighting_feature(backshellLight);
		delay_ms(30);
	}*/
				
	while (1)
	{
		
		//svc_ATTD_btn();
		svc_DND_btn();
		svc_TTL_btn();
		//delay_ms(400);
		
		
		
		
		for (i=0; i<100; i++){
			backshellLight.pwmRaw_B = i;
			backshellLight.pwmRaw_G = 100-i;
			write_RGBlighting_feature(backshellLight);
			//readingLight2.pwmRaw = i;
			//write_lighting_feature(readingLight2);
			delay_ms(30);//DIMMING_RATE);			
			//svc_DND_btn();
		}
		for (i=0; i<100; i++){
			backshellLight.pwmRaw_B = 100-i;
			backshellLight.pwmRaw_G = i;
			write_RGBlighting_feature(backshellLight);
			//readingLight2.pwmRaw = 100-i;
			//write_lighting_feature(readingLight2);
			delay_ms(30);//DIMMING_RATE);			
			//svc_DND_btn();
		}
		
		/*
		data = test_timer();
		printf ("Timer 1: %" PRIu64 "\n", data);
		delay_ms(500);
		data = test_timer();
		printf ("Timer 2: %" PRIu64 "\n", data);
		*/
		delay_ms(10);
		
	}

	// Close I2C session
	i2c_end();
	
	// Close bcm2835 library and deallocate memory
	close_bcm();
		
	return 0;
}

