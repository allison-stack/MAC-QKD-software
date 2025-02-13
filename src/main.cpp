// Getting date and time from NTP server: https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/

#include <WiFi.h>
#include "time.h"

#define LED 2

const char* ssid       = "";  // insert wifi name here
const char* password   = "";  // insert wifi password here

const char* ntpServer = "pool.ntp.org";  // want to connect to this server to get time
const long  gmtOffset_sec = -5 * 3600;  // EST is UTC-5
const int   daylightOffset_sec = 3600;  // Daylight Saving Time offset (1 hour)

// variable and function definitions go up here
bool isConnected = false;
void printLocalTime();

void setup()
{
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);


}

void loop()
{
  delay(1000);
  printLocalTime();
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  // print date, day of the week, month, day, year, hour, minute, and second in serial terminal
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println();
}