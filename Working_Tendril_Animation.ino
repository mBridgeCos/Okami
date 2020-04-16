#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 64 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 5
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) {leds[i].nscale8(220); } }

void loop() {
   
	static uint8_t hue = 95;  // 0  is a green , 100 is a magenta, 75 is yellow, 130 is purple, 90 orange, 95 red/orange, 
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
    if(i==0){
      hue = 95;
    }
		if(i == 10){
      hue = 75;
		}
		if (i == 50){
      hue = 25;
		}
    leds[i] = CHSV(hue, 255, 255);
		// Show the leds
		FastLED.show(); 
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
  for(int i = 39; i < NUM_LEDS; i++){
     for(int z = 0; z < 25; z++){
        leds[i].nscale8( 192);
        if(z == 0 || z == 10 || z == 20){ 
           FastLED.show();
        }
     }
 
  }
  delay(1000);
}
