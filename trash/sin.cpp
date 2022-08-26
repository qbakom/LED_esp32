#include <Arduino.h>
#include <FastLED.h>

#include <TFT_eSPI.h> 
#include <SPI.h>
#include "WiFi.h"
#include <Wire.h>
#include <Button2.h>
#include "esp_adc_cal.h"

#ifndef TFT_DISPOFF
#endif

#ifndef TFT_SLPIN
#endif

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0

int ledPin = 27;
int analogPin = 3;
int cx=0;
int leds_num = 40;
CRGB leds[36];

int pom = 0;
int bri = 10;
int wsk = 0;
int count = 0;
int gr = 0;
int red = 1;
int blue = 10;


int counter = 0;

void setup() 
{
  FastLED.addLeds<WS2812, 27, GRB>(leds, leds_num);
}

// void turn_off()
// {
//   for (int i = 0; i <= 40; i++)
//     leds[i] = CRGB(0, 0, 0);
//   FastLED.show();
// }

void loop() 
{   
    
    // if (counter++ >= 5)
    // {
    //   for (int i = 0; i <= leds_num; i++)
    //     leds[i] = CRGB(0, 0, 0);
    //   FastLED.show();
    //   return;
    // }

    for(int i = 0; i <= leds_num; i++)
    {

        if (count < 7)
        {
          if (count < 4)
            wsk = count;
          else if (count == 4)
            wsk = 2;
          else
            wsk = 6 - count;

          leds[i] = CRGB(bri * wsk * wsk * red, bri * wsk * wsk * gr, blue);
          count++;
        }
        else
        {
          count = 1;
          pom = gr;
          gr = red;
          red = pom;
        }
    }
    blue += 1;
    FastLED.show();
    delay(150);

}