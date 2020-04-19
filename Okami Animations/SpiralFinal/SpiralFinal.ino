/*
 * Meteor Shower posted by Chemdoc77
 * Based on the outstanding MeteorShower sketch by Jon Burroughs as seen in Adam bluebottleyellowboxyellyfish’s clock
 * which Chemdoc77 slightly modified.
 */


#include <FastLED.h>

#define LED_PIN 13
#define CHIPSET NEOPIXEL 
#define NUM_LEDS 25

#define BRIGHTNESS 100
CRGB leds[NUM_LEDS];


byte ledsX[NUM_LEDS][3];
uint8_t hue = 20;
uint16_t timeframe;
byte idex = 0;
byte colorTIP = 0;
byte meteorLENGTH;
byte loopCount = 1;    //low number loop counter

void setup() {

  delay(1000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);
  set_max_power_indicator_LED(13);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

}

//============================================
void loop() {
  
  meteorShower();

}

//=============== Functions ==============

void meteorShower(){
  //hue master
  hue++;  
 
  //populate the leds[] with stored ledsX[] array data
  for(byte i = 0; i < NUM_LEDS; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }
  //clear the previous counter clockwise position
  byte iCCW;
 
  //we are keeping track of elapsed time
  timeframe++;    //fx timer

   meteorLENGTH = random8(7, 38);
 
   //increment the meteor display frame
   idex++;
   //make sure we don't drift into space
   if (idex > meteorLENGTH) { idex = 0; }   
   
  //meteorLENGTH is randomized during this timeframe only
  if((timeframe > 790) && (timeframe <= 1090)) { meteorLENGTH = random8(3, 12); }
 
  //during this point in the animation timeframe
  if(timeframe == 1180) {
    //reset the timeframe
    timeframe = 0;
    //increment the loop counter
    loopCount++;
  }
 
  //during this part of the loopCount, all meteors have a white colored tip
  if(loopCount == 1) { colorTIP = 0; }
  if(loopCount == 2) { colorTIP = 1; }
  //end of the desired fx, reset the variable for the next time around
  if(loopCount == 3) {
    colorTIP = 0;
    loopCount = 0;
  }
 
  //there are two switch case statements nestled into one another
  //we always want to control the color of the meteor tip
  //the other controls the actual meteor animation in 45 frames/case statements
  switch (idex) {
  case 0:
    switch (colorTIP){
    case 0:
      hue = 20;
      leds[0] = CHSV(20, 255, 255);
      break;
    case 1:
      hue = 40;
      leds[0] = CHSV(40,255,255);
      break;
      }
    break;
    
  case 1:
    leds[0] = CHSV((hue - 20), 255, 210);
    break;
  case 2:
    leds[0] = CHSV((hue - 22), 255, 180);
    break;
  case 3:
    leds[0] = CHSV((hue - 23), 255, 150);
    break;
  case 4:
    leds[0] = CHSV((hue - 24), 255, 110);
    break;
  case 5:
    leds[0] = CHSV((hue - 25), 255, 90);
    break;
  case 6:
    leds[0] = CHSV((hue - 27), 160, 60);
    break;
  case 7:
    leds[0] = CHSV((hue - 29), 140, 40);
    break;
  case 8:
    leds[0] = CHSV((hue - 30), 120, 20);
    break;
  case 9:
    leds[0] = CHSV((hue - 41), 100, 20);
    break;
  case 10:
    leds[0] = CRGB::Black;
    break;
  case 11:
    leds[0] = CRGB::Black;
    break;
  case 12:
    leds[0] = CRGB::Black;
    break;
  case 13:
    leds[0] = CRGB::Black;
    break;
  case 14:
    leds[0] = CRGB::Black;
    break;
  case 15:
    leds[0] = CRGB::Black;
    break;
  }
  //copy the LED Array
  for(byte i = 1; i < NUM_LEDS; i++ ) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  //show the blinky
  FastLED.show();  
  //control the animation speed/frame rate
  delay(25);
}
 
//find the adjacent counter clockwise postion of the led
//funkboxing code snippet
byte adjacent_ccw(byte i) {
  byte r;
  if (i > 0) { r = i - 1; }
  else { r = NUM_LEDS - 1; }
  return r;  
}
