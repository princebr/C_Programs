

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <functions.h>
#include <config.h>


char wbuf[MAX_LEN];
char rbuf[MAX_LEN];


char led0_on[] = {LED0_ON_L, 0x00, 0x00, 0x00, 0x00};

// TEST Buffers
char led2_on[] = {LED2_ON_L, 0x00, 0x00, 0x10, 0x00};
char led2_off[] = {LED2_ON_L, 0x00, 0x00, 0x00, 0x00};
//--------------

char all_on[] = {ALL_LED_ON, 0xBB};
char all_off[] = {ALL_LED_OFF, 0x00};


//uint8_t slave_address = 0x42;
//uint8_t data;

uint8_t init_bcm(void)
{
	printf("Initialize BCM... \n");
	
	if (!bcm2835_init())
		return 1;
	
	else
	{
		// Set CapTouch I/O to inputs
		bcm2835_gpio_fsel(SW1, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(SW2, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(SW3, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(SW4, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(SW5, BCM2835_GPIO_FSEL_INPT);
		
		// Set uSW I/O to inputs
		bcm2835_gpio_fsel(NEU_USW, BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(LAY_USW, BCM2835_GPIO_FSEL_INPT);
		
		// Clear EDS registers for uSW
		bcm2835_gpio_ren(NEU_USW);
		bcm2835_gpio_ren(LAY_USW);
		bcm2835_gpio_set_eds(NEU_USW);
		bcm2835_gpio_set_eds(LAY_USW);
		
		
		// Set Relay I/O to outputs
		bcm2835_gpio_fsel(TTL_SW, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_fsel(NEU_SW, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_fsel(LAY_SW, BCM2835_GPIO_FSEL_OUTP);
		
		// Set Status LED output
		bcm2835_gpio_fsel(ST_LED, BCM2835_GPIO_FSEL_OUTP);

		// Set Amplifier Mute output
		bcm2835_gpio_fsel(MUTE, BCM2835_GPIO_FSEL_OUTP);
		
		//bcm2835_i2c_setSlaveAddress(PCA1);
		bcm2835_i2c_begin();
		
		printf("Init BCM done. \n");
		return 0;
	}	
}


void init_periph(void)
{
	uint8_t data = 0;
	
	printf("Initialize PCA1... \n");
	bcm2835_i2c_setSlaveAddress(PCA1);
	data = bcm2835_i2c_write(autoinc_msg, 2);
	printf("Write Result (Autoinc) = %d\n", data); 
	delay(1);
	data = bcm2835_i2c_write(cfg_msg, 2);
	printf("Write Result (Config) = %d\n", data); 
	delay(1);
	
	printf("Initialize PCA2... \n");
	bcm2835_i2c_setSlaveAddress(PCA2);
	data = bcm2835_i2c_write(autoinc_msg, 2);
	printf("Write Result (Autoinc) = %d\n", data); 
	delay(1);
	data = bcm2835_i2c_write(cfg_msg, 2);
	printf("Write Result (Config) = %d\n", data); 
	delay(1);
	
	return;
}


void set_initial_conditions(void)
{
	//Turn on Status LED
	set_led(ST_LED);

	// Mute Audio Amplifier
	mute_audio();
	
	//***********************************/
	// Reading Light Hack - use .state 
	readingLight1.pwmRaw = RL_DEFAULT_MAX;
	readingLight.intensity = RL_DEFAULT_MAX;
	readingLight.state = RL1;
	//***********************************/
	
	// Set Reading Light 1
	readingLight1.state = OFF;
	readingLight1.pwmRaw = RL_DEFAULT_MAX;
	readingLight1.address = CH7_BASE;
	readingLight1.device = PCA1;

	// Set Reading Light 2
	readingLight2.state = OFF;
	readingLight2.pwmRaw = RL_DEFAULT_MAX;
	readingLight2.address = CH8_BASE;
	readingLight2.device = PCA1;

	// Set Cap TTL Light
	capTTLLight.state = OFF;
	capTTLLight.pwmRaw = CAP_LIGHT_DEFAULT;
	capTTLLight.address = CH6_BASE;
	capTTLLight.device = PCA1;

	// Set Cap LAY Light
	capLAYLight.state = OFF;
	capLAYLight.pwmRaw = CAP_LIGHT_DEFAULT;
	capLAYLight.address = CH5_BASE;
	capLAYLight.device = PCA1;
	
	// Set Cap RL Light
	capRLLight.state = OFF;
	capRLLight.pwmRaw = CAP_LIGHT_DEFAULT;
	capRLLight.address = CH4_BASE;
	capRLLight.device = PCA1;

	// Set Cap DND White
	capDNDWhiteLight.state = OFF;
	capDNDWhiteLight.pwmRaw = CAP_LIGHT_DEFAULT;
	capDNDWhiteLight.address = CH2_BASE;
	capDNDWhiteLight.device = PCA1;

	// Set Cap DND Red
	capDNDRedLight.state = OFF;
	capDNDRedLight.pwmRaw = 0;
	capDNDRedLight.address = CH3_BASE;
	capDNDRedLight.device = PCA1;
	
	// Set Cap ATTD White
	capATTDWhiteLight.state = OFF;
	capATTDWhiteLight.pwmRaw = CAP_LIGHT_DEFAULT;
	capATTDWhiteLight.address = CH0_BASE;
	capATTDWhiteLight.device = PCA1;

	// Set Cap ATTD Blue
	capATTDBlueLight.state = OFF;
	capATTDBlueLight.pwmRaw = 0;
	capATTDBlueLight.address = CH1_BASE;
	capATTDBlueLight.device = PCA1;
			
	// Set Backshell Light
	backshellLight.state = OFF;
	backshellLight.pwmRaw_R = RGB_R_DEFAULT;
	backshellLight.pwmRaw_G = RGB_G_DEFAULT;
	backshellLight.pwmRaw_B = RGB_B_DEFAULT;
	backshellLight.address = CH10_BASE;
	backshellLight.device = PCA1;

	// Set Footwell Light
	footwellLight.state = OFF;
	footwellLight.pwmRaw_R = RGB_R_DEFAULT;
	footwellLight.pwmRaw_G = RGB_G_DEFAULT;
	footwellLight.pwmRaw_B = RGB_B_DEFAULT;
	footwellLight.address = CH3_BASE;
	footwellLight.device = PCA2;
	
	// Set Under IFE Light
	underIFELight.state = OFF;
	underIFELight.pwmRaw_R = RGB_R_DEFAULT;
	underIFELight.pwmRaw_G = RGB_G_DEFAULT;
	underIFELight.pwmRaw_B = RGB_B_DEFAULT;
	underIFELight.address = CH0_BASE;
	underIFELight.device = PCA2;
	
	// Set Stowage Light
	stowageLight.state = OFF;
	stowageLight.pwmRaw_R = RGB_R_DEFAULT;
	stowageLight.pwmRaw_G = RGB_G_DEFAULT;
	stowageLight.pwmRaw_B = RGB_B_DEFAULT;
	stowageLight.address = CH13_BASE;
	stowageLight.device = PCA1;	
		
	return;
}

/* -------------- Write to Single Lighting Features ----------------- */
void write_lighting_feature(struct ledFeature feature)
{
	// break pwmRaw values into ~OFF_L and ~OFF_H
	uint8_t ledx_on_h = 0;
	uint8_t ledx_on_l = 0;
	uint8_t ledx_off_l = feature.pwmRaw & 0xFF;
	uint8_t ledx_off_h = feature.pwmRaw >> 8;
	
	// assemble message
	uint8_t msg[] = {feature.address,
		ledx_on_l, ledx_on_h, ledx_off_l, ledx_off_h
	};
	
	// Debug line
	//printf("%d %d %d %d\n", ledx_on_l, ledx_on_h, ledx_off_l, ledx_off_h);
	
	// set i2c address based on feature.device
	bcm2835_i2c_setSlaveAddress(feature.device);
	
	// Send message
	bcm2835_i2c_write(msg, sizeof(msg));
	return;
}

/* ---------------- Write to RGB Lighting Features ------------------ */
void write_RGBlighting_feature(struct ledRGBFeature feature)
{
	// break pwmRaw values into ~OFF_L and ~OFF_H
	uint8_t ledx_on_h = 0;
	uint8_t ledx_on_l = 0;
	uint8_t ledr_off_l = feature.pwmRaw_R & 0xFF;
	uint8_t ledr_off_h = feature.pwmRaw_R >> 8;
	uint8_t ledg_off_l = feature.pwmRaw_G & 0xFF;
	uint8_t ledg_off_h = feature.pwmRaw_G >> 8;
	uint8_t ledb_off_l = feature.pwmRaw_B & 0xFF;
	uint8_t ledb_off_h = feature.pwmRaw_B >> 8;
	
	// assemble message
	uint8_t msg[] = {feature.address,
		ledx_on_l, ledx_on_h, ledr_off_l, ledr_off_h,
		ledx_on_l, ledx_on_h, ledg_off_l, ledg_off_h,
		ledx_on_l, ledx_on_h, ledb_off_l, ledb_off_h
	};
	
	// set i2c address based on feature.device
	bcm2835_i2c_setSlaveAddress(feature.device);
	
	// Send message
	bcm2835_i2c_write(msg, sizeof(msg));
	return;
}



void i2c_end(void)
{
	bcm2835_i2c_end(); 
	return;
}


void close_bcm(void)
{
	bcm2835_close();
	return;
}


void delay_ms(unsigned int ms)
{
	bcm2835_delay(ms);
	return;
}


uint64_t test_timer(void)
{
	return bcm2835_st_read();
}


/* --------- SWITCH ACTIONS --------- */
void svc_NEU_usw(void)
{
	//if (bcm2835_gpio_eds(NEU_USW))
	if (bcm2835_gpio_lev(NEU_USW) & readingLight.state == RL1)
	{
		//if (readingLight.state == RL1)
		//{
			readingLight.state = RL2;
			readingLight1.pwmRaw = 0;
			readingLight2.pwmRaw = RL_DEFAULT_MAX;
			write_lighting_feature(readingLight1);
			write_lighting_feature(readingLight2);
	}
	else if (!bcm2835_gpio_lev(NEU_USW) & readingLight.state == RL2)
	{
			readingLight.state = RL1;
			readingLight1.pwmRaw = RL_DEFAULT_MAX;
			readingLight2.pwmRaw = 0;
			write_lighting_feature(readingLight1);
			write_lighting_feature(readingLight2);
	}
			
		// dim lighting
		// toggle reading lights
		
		// Clear EDS register
		bcm2835_gpio_set_eds(NEU_USW);
	//}
	
	return;
}


void svc_LAY_usw(void)
{
	if (bcm2835_gpio_eds(LAY_USW))
	{
		printf("LAY uSW \n");
		// dim lighting
		// unmute audio
		bcm2835_gpio_set_eds(LAY_USW);
	}
	
	return;
}


/* --------- BTN ACTIONS --------- */
uint8_t poll_ATTD_btn(void)
{
	return bcm2835_gpio_lev(SW1);
}


uint8_t poll_DND_btn(void)
{
	return bcm2835_gpio_lev(SW2);
}

void svc_ATTD_btn(void)
{
	if (!bcm2835_gpio_lev(SW1)) {
		printf("State: %d\n", capATTDWhiteLight.state);
		if (capATTDWhiteLight.state == WHITE) {
			capATTDWhiteLight.pwmRaw = 0;
			capATTDBlueLight.pwmRaw = CAP_LIGHT_DEFAULT;
			write_lighting_feature(capATTDWhiteLight);
			write_lighting_feature(capATTDBlueLight);
			
			capATTDWhiteLight.state = BLUE;
		}
		else {
			capATTDWhiteLight.pwmRaw = CAP_LIGHT_DEFAULT;
			capATTDBlueLight.pwmRaw = 0;
			write_lighting_feature(capATTDWhiteLight);
			write_lighting_feature(capATTDBlueLight);
			
			capATTDWhiteLight.state = WHITE;
		}
		
		// "Loop Debounce"
		delay_ms(500);
	}
	
	return;
}

void svc_DND_btn(void)
{
	if (!bcm2835_gpio_lev(SW2)) {
		printf("State: %d\n", capDNDWhiteLight.state);
		if (capDNDWhiteLight.state == WHITE) {
			capDNDWhiteLight.pwmRaw = 0;
			capDNDRedLight.pwmRaw = CAP_LIGHT_DEFAULT;
			write_lighting_feature(capDNDWhiteLight);
			write_lighting_feature(capDNDRedLight);
			
			capDNDWhiteLight.state = BLUE;
		}
		else {
			capDNDWhiteLight.pwmRaw = CAP_LIGHT_DEFAULT;
			capDNDRedLight.pwmRaw = 0;
			write_lighting_feature(capDNDWhiteLight);
			write_lighting_feature(capDNDRedLight);
			
			capDNDWhiteLight.state = WHITE;
		}
		
		//  "Loop Debounce"
		delay_ms(500);
	}
	return;
}


void svc_RL_btn(void)
{
	if (!bcm2835_gpio_lev(SW3)) {
		capRLLight.pwmRaw = 1000;
		write_lighting_feature(capRLLight);
		
		// Add toggle for reading lights...
	}
	else {
		capRLLight.pwmRaw = CAP_LIGHT_DEFAULT;
		write_lighting_feature(capRLLight);
	}
	return;
}


void svc_LAY_btn(void)
{
	if (!bcm2835_gpio_lev(SW4)) {
		capLAYLight.pwmRaw = 1000;
		write_lighting_feature(capLAYLight);
		bcm2835_gpio_write(LAY_SW, HIGH);
	}
	else {
		capLAYLight.pwmRaw = CAP_LIGHT_DEFAULT;
		write_lighting_feature(capLAYLight);
		bcm2835_gpio_write(LAY_SW, LOW);
	}
	return;
}

void svc_TTL_btn(void)
{
	if (!bcm2835_gpio_lev(SW5)) {
		capTTLLight.pwmRaw = 1000;
		write_lighting_feature(capTTLLight);
		bcm2835_gpio_write(TTL_SW, HIGH);
	}
	else {
		capTTLLight.pwmRaw = CAP_LIGHT_DEFAULT;
		write_lighting_feature(capTTLLight);
		bcm2835_gpio_write(TTL_SW, LOW);
	}
	return;
}

/* ------------------------------- */

/* --------- LED ACTIONS --------- */
void set_led(uint8_t led)
{
	bcm2835_gpio_write(led, HIGH);
	return;	
}

void clear_led(uint8_t led)
{
	bcm2835_gpio_write(led, LOW);
	return;	
}

void toggle_led(uint8_t led)
{
	if (bcm2835_gpio_lev(led))
		bcm2835_gpio_write(led, LOW);
	else
		bcm2835_gpio_write(led, HIGH);
	return;
}

/* ------------------------------- */

/* -------- AUDIO ACTIONS -------- */

void mute_audio(void)
{
	bcm2835_gpio_write(MUTE, HIGH);
	return;
}

void unmute_audio(void)
{
	bcm2835_gpio_write(MUTE, LOW);
	return;
}
