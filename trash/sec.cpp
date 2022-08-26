#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "WiFi.h"
#include <Wire.h>
#include <Button2.h>
#include "esp_adc_cal.h"

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0

#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9

int ledPin = 9;
int analogPin = 3;
int val = 0;

int brightness = 255;
int gBright = 0;
int rBright = 0;
int bBright = 0;

int fadeSpeed = 10;

void setup() 
{
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    TurnOn();
    delay(5000);
    TurnOff();
}

void TurnOn() 
{ 
   for (int i = 0; i < 256; i++) {
       analogWrite(RED_LED, rBright);
       rBright +=1;
       delay(fadeSpeed);
   }
 
   for (int i = 0; i < 256; i++) {
       analogWrite(BLUE_LED, bBright);
       bBright += 1;
       delay(fadeSpeed);
   } 
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, gBright);
       gBright +=1;
       delay(fadeSpeed);
   } 
}


void TurnOff() 
{
   for (int i = 0; i < 256; i++) {
       analogWrite(GREEN_LED, brightness);
       analogWrite(RED_LED, brightness);
       analogWrite(BLUE_LED, brightness);
 
       brightness -= 1;
       delay(fadeSpeed);
   }
}

void loop() 
{
    val = analogRead(analogPin);
}