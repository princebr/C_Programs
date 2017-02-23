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

//#include <bcm2835.h>
#include <wiringPi.h>
#include <stdio.h>

#define PIN 21
//#define PIN RPI_V2_GPIO_P1_29


int main(int argc, char **argv)
{
	//printf ("starting:");
	
	wiringPiSetup();
	pinMode(PIN, OUTPUT);
	
		
	while(1)
	{	
		digitalWrite(PIN, HIGH);
		//printf ("high");
		delay(500);
		
		digitalWrite(PIN, LOW);
		//printf ("low");
		delay(500);
		
	}
	
	return 0;
}

