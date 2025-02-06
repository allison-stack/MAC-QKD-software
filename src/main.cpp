#include <WiFi.h>
#include "time.h"

#define LED 2

const char* ssid       = "";
const char* password   = "";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void setup()
{
  Serial.begin(921600);

  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  
  Serial.println("starting");
}

bool isConnected = false;

void loop()
{
  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Connected");
    digitalWrite(LED, HIGH);
    isConnected = true;
    
  }

  if (WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    digitalWrite(LED, !digitalRead(LED));
    delay(1000);
    isConnected = false;
  }
}