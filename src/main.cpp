#include <WiFi.h>
#include "time.h"

#define LED 2

const char* ssid       = "";  // insert wifi name here
const char* password   = "";  // insert wifi password here

const char* ntpServer = "pool.ntp.org";  // want to connect to this server to get time
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

// variable definitions go up here
bool isConnected = false;

void setup()
{
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  
  Serial.println("starting");
}

void loop()
{
  // ESP32 is connected to wifi
  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Connected");
    digitalWrite(LED, HIGH);
    isConnected = true;
    
  }

  // ESP32 is not connected to wifi
  if (WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    digitalWrite(LED, !digitalRead(LED));
    delay(1000);
    isConnected = false;
  }
}