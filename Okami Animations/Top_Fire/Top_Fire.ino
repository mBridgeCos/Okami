#include <FastLED.h>
#include <pixeltypes.h>

#define LED_PIN     8
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    20

#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 30

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];
CRGB leds_temp[NUM_LEDS/2];  //ADDED THIS

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
CRGBPalette16 gPal;

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
     gPal = CRGBPalette16( CRGB::Black, CRGB::DarkRed, CRGB::Orange, CRGB::Yellow);
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  Fire2012_halfStrip(); 
  mirror2ndHalf(); 
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  90 //45

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 50 //130


void Fire2012_halfStrip() //Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS/2];

  // Step 1.  Cool down every cell a little
    for( byte i = 0; i < NUM_LEDS/2; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( byte k= NUM_LEDS /2; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      byte y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( byte j = 0; j < NUM_LEDS/2; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
        for( byte j = 0; j < NUM_LEDS/2; j++) {
          CRGB color = HeatColor( heat[j]);
          leds_temp[j] = color;
        }
    }
}

//---------------------------------------------------------------
void mirror2ndHalf() {
  //copy and mirror pixel data from leds_temp to leds array.

  if (gReverseDirection == false) {  //false is center outward should always be false
    for (uint8_t i=0; i<NUM_LEDS/2; i++) {
      leds[(NUM_LEDS/2)-1-i] = leds_temp[i];
      leds[(NUM_LEDS/2)+i] = leds_temp[i];
    }
  }
  
}//end_mirror2ndHalf
