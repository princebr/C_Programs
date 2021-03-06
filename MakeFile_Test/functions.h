	
// Single Channel Lighting Features ---
struct ledFeature {
	uint8_t state;
	uint16_t pwmRaw;
	uint16_t address;
	uint8_t device;
	};

struct ledFeature readingLight1;
struct ledFeature readingLight2;
struct ledFeature capTTLLight;
struct ledFeature capLAYLight;
struct ledFeature capRLLight;
struct ledFeature capDNDWhiteLight;
struct ledFeature capDNDRedLight;
struct ledFeature capATTDWhiteLight;
struct ledFeature capATTDBlueLight;
//-------------------------------------

// 3 Channel Lighting Features --------
struct ledRGBFeature {
	uint8_t state;
	uint16_t pwmRaw_R;
	uint16_t pwmRaw_G;
	uint16_t pwmRaw_B;
	uint16_t address;
	uint8_t device;
	};

struct ledRGBFeature backshellLight;
struct ledRGBFeature footwellLight;	// Contains "pinlight" as well
struct ledRGBFeature underIFELight;
struct ledRGBFeature stowageLight;
//--------------------------------------


uint8_t init_bcm(void);
void init_periph(void);
void set_initial_conditions(void);
void write_lighting_feature(struct ledFeature);
void write_RGBlighting_feature(struct ledRGBFeature);
void i2c_end(void);
void close_bcm(void);
void delay_ms(unsigned int);
uint64_t test_timer(void);
uint8_t poll_ATTD_btn(void);
uint8_t poll_DND_btn(void);
void svc_ATTD_btn(void);
void svc_DND_btn(void);
void set_led(uint8_t);
void clear_led(uint8_t);
void toggle_led(uint8_t);

