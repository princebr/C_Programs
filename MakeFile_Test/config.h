

/* ------------------------ OUTPUTS --------------------------------- */
#define ST_LED RPI_V2_GPIO_P1_32	// Status LED
#define MUTE RPI_V2_GPIO_P1_7		// Amplifier Mute pin


/* ------------------------ INPUTS ---------------------------------- */
#define SW1 RPI_V2_GPIO_P1_29
#define SW2 RPI_V2_GPIO_P1_31
#define SW3 RPI_V2_GPIO_P1_33
#define SW4 RPI_V2_GPIO_P1_35
#define SW5 RPI_V2_GPIO_P1_37

/* ----------------------- LIGHTING CONSTANTS ----------------------- */
#define MODE_READ 0
#define MODE_WRITE 1
#define MAX_LEN 32

#define DIMMING_RATE	5	// Higher is slower...

#define RGB_R_DEFAULT	10
#define RGB_G_DEFAULT	0
#define RGB_B_DEFAULT	0

#define CAP_LIGHT_DEFAULT	200
#define RL_DEFAULT_MAX		2000

#define OFF 	0;
#define ON 		1;
#define WHITE 	2;
#define BLUE	3;
#define RED		4;

/* ------------------------ PCA9685 CONSTANTS ----------------------- */
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

#define CH0_BASE 0x06
#define CH1_BASE 0x0A
#define CH2_BASE 0x0E
#define CH3_BASE 0x12
#define CH4_BASE 0x16
#define CH5_BASE 0x1A
#define CH6_BASE 0x1E
#define CH7_BASE 0x22
#define CH8_BASE 0x26
#define CH9_BASE 0x2A
#define CH10_BASE 0x2E
#define CH11_BASE 0x32
#define CH12_BASE 0x36
#define CH13_BASE 0x3A
#define CH14_BASE 0x3E
#define CH15_BASE 0x42

#define PCA1 0x42
#define PCA2 0x41

char mode_msg[] = {MODE1, 0x80};		// MODE1 => 0x01, reset chip
char autoinc_msg[] = {MODE1, 0xA1}; 	// MODE1 => 0xA1, auto-increment
char cfg_msg[] = {MODE2, 0x04}; 		// MODE2 => 0x04, hardware configuration
