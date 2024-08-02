#include <Arduino.h>
#include <FastLED.h>

#include <stdbool.h>
#include "soc/soc.h"
#include "soc/gpio_periph.h"
#include "soc/gpio_struct.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "SPI.h"
#include "TFT_eSPI.h"
#include "WiFi.h"
#include <Wire.h>
#include <Button2.h>
#include "esp_adc_cal.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "SPI.h"
#include "TFT_eSPI.h"


#include "Button2.h"
#ifndef TFT_DISPOFF
#endif

#ifndef TFT_SLPIN
#endif

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0


using std::string;

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
int blue = 0;


const char* ssid = "p-v";
const char* password = "3.1415926";
WebServer server(80);

int counter = 0;

int period = 0;

void handleRoot() {
  counter = -100;
  Serial.println(server.args());
  for (uint8_t i = 0; i < server.args(); i++) {
   if (server.argName(i) == "period") period = atoi(server.arg(i).c_str());
   if (server.argName(i) == "brightness") bri = atoi(server.arg(i).c_str());
  }

  server.send(200, "text/html", "<html>"
  "<head><style>html { font-family: Times New Roman,Arial,sans-serif; display: inline-block; margin: 0px auto; text-align: center;}"
  "text-decoration: none; font-size: 30px; margin: 2px;}"
  "</style></head>"
  "<body>"
  "<p>LED settings:</p>"
  "<form target=ifr><input type=range id=userInput name=period min=0 max=20 step=1 onchange=\"this.form.submit();\"><label for=period>Period</label></input>"
  "<input type=range name=brightness min=0 max=100 step=5 onchange=\"this.form.submit();\"><label for=brightness>Brightness</label></input>"
  "</form>"
  // "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>"
  "<iframe name=ifr style=\"display:none\"></iframe>"
  "</body></html>");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  } 
  server.send(404, "text/plain", message);
}

void setup() 
{
  
  FastLED.addLeds<WS2812, 27, GRB>(leds, leds_num);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void turn_off()
{
  for (int i = 0; i <= 40; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
}


void loop() 
{   
    server.handleClient();
    if (counter++ >= 20)
    {
      for (int i = 0; i <= leds_num; i++)
        leds[i] = CRGB(0, 0, 0);
      FastLED.show();
      return;
    }

    for(int i = 0; i <= leds_num; i++)
    {

        if (count < period + 1)
        {
          if (count < period/2 + 1)
            wsk = count;
          else if (count == period/2 + 1)
            wsk = period/2 - 1;
          else
            wsk = period - count;

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