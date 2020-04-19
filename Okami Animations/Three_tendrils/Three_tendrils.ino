// MultiArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with

#include <FastLED.h>

#define CHIPSET NEOPIXEL
#define BRIGHTNESS 85
#define NUM_LEDS_PER_TEND_LONG 30
#define NUM_LEDS_PER_TEND_MED 20
#define NUM_LEDS_PER_TEND_SHORT 9
#define CLOCK_PIN 13

CRGB tendLeds_L[NUM_LEDS_PER_TEND_LONG];
CRGB tendLeds_M[NUM_LEDS_PER_TEND_MED];
CRGB tendLeds_S[NUM_LEDS_PER_TEND_SHORT];

// addLeds multiple times, once for each strip
void setup() {
  
  delay(1000); // sanity delay
  // tell FastLED there's 30 leds on pin 5 Tendril Long
  LEDS.addLeds<WS2812,5,RGB>(tendLeds_L, NUM_LEDS_PER_TEND_LONG);
  
  // tell FastLED there's 20 leds on pin 9 Tendril Medium
  LEDS.addLeds<WS2812,9,RGB>(tendLeds_M, NUM_LEDS_PER_TEND_MED);
    
  // there are 9 LEDs for on pin 11 Tendril Short
  LEDS.addLeds<WS2812,11,RGB>(tendLeds_S, NUM_LEDS_PER_TEND_SHORT);
  
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);

}

//=========================================== MAIN =====================================================

void loop() {
  
  static uint8_t hue_L = 95;  // 0  is a green , 100 is a magenta, 75 is yellow, 130 is purple, 90 orange, 95 red/orange, 
  static uint8_t hue_M = 95;
  static uint8_t hue_S = 95;
  // Begin animation
  for(int i = 0; i < NUM_LEDS_PER_TEND_LONG; i++) {
    // Set the colors
    if(i==0){
      hue_L = 95; // Red
      hue_M = 95;
      hue_S = 95;
    }
    if(i == 3){
      hue_S = 75;
    }
    if(i == 5){
      hue_L = 75; // Yellow
      hue_M = 75;
      hue_S = 30; // Green
    }
    if(i == 16){
      hue_M = 30;
    }
    if (i == 20){
      hue_L = 30; // Green
    }
    if(i < 20){
       tendLeds_L[i] = CHSV(hue_L, 255, 255);
       tendLeds_M[i] = CHSV(hue_M, 255, 255);
       if(i < 9){
        tendLeds_S[i] = CHSV(hue_S, 255, 255);
       }
    } else {
       tendLeds_L[i] = CHSV(hue_L, 255, 255);
    }
    // Show the leds
    FastLED.show(); 
    fadeall();
    // Wait a little bit before we loop around and do it again (speed) higher = slower
    delay(60);
  }
  for(int i = 0; i < NUM_LEDS_PER_TEND_LONG; i++){
     for(int z = 0; z < 25; z++){
        tendLeds_L[i].nscale8( 175);  // original 192
        tendLeds_M[i].nscale8(175);
        tendLeds_S[i].nscale8(175);
        if(z == 0 || z == 12 || z == 24){ 
           FastLED.show();
           delay(4);
        }
     }
  }
  delay(1000);

}
// handles fade of tendril animation
void fadeall() { 
    for(int i = 0; i < 30; i++) {
      tendLeds_L[i].nscale8(220);
      tendLeds_M[i].nscale8(220);
      tendLeds_S[i].nscale8(220);
    } 
}
