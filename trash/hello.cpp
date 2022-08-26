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

#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9

int ledPin = 9;
int analogPin = 3;
int val = 0;

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

//! Long time delay, it is recommended to use shallow sleep, which can effectively reduce the current consumption
void espDelay(int ms) //use-> espDelay(6000);
{   
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");
    tft.init();
    tft.fontHeight(2);
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Hello world", tft.width()/4, tft.height() / 2, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void loop()
{

}
