#include <FastLED.h>

#define NUM_LEDS 8
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

byte  r, g, b;

void setup() {
  // init the LED object
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // set random seed
  randomSeed(analogRead(0));
}


void loop() {
  // loop over the NUM_LEDS
  for (int cur = 0; cur < NUM_LEDS; cur++) {
    // chose random value for the r/g/b
    r = random(0, 255);
    g = random(0, 255);
    b = random(0, 255);

    //set the value to the led
    leds[cur] = CRGB (r, g, b);

    // set the colors set into the phisical LED
    FastLED.show();

    // delay 50 millis
    FastLED.delay(200);
  }


}
