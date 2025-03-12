#include <Arduino.h>
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
int keyLength = 32;
int aliceBasisSelection[32];  // Array to store basis selections
unsigned long aliceTimestamps[32];  // Array to store timestamps

void printLocalTime();
void generateBasisSelection();
void sendBits();
void receiveDataFromBob();

// Alice's side

void setup() {
  // time syncronization with bob
  Serial.begin(9600);

  // connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // initialize and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect wifi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  // generate random basis selection
  generateBasisSelection();

  // send bits to Bob
  sendBits();

  // receive data from Bob and compare
  receiveDataFromBob();

  // determine key length
    // account for the fact that they will loose some bits so add approx 50% more bits to basis selection and bits sent

  // send data to Bob
    // array of basis and timestamps
  
  // recive Bobs data
    // compare the timestamps to ensure the bit sent is the same bit recieved
    // if the bits are the same compare basis selection
      // if basis are same keep bit for the key (if not discard the bit)
}

void loop() {
  // empty
}

// print current time
void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
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

// determine basis slection at begining and store in array
void generateBasisSelection() {
  for (int i = 0; i < keyLength; i++) {
    // Random basis (either 0 or 1)
    aliceBasisSelection[i] = esp_random() & 0x01;
  }
}

// send X number of bits using the random basis array
void sendBits() {
  for (int i = 0; i < keyLength; i++) {
    // set the wave plate according to the basis selection
    Serial.print("Setting wave plate to basis: ");
    Serial.println(aliceBasisSelection[i]);

    // send pulse
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);

    // record timestamp of pulse
    aliceTimestamps[i] = millis();

    // ensure enough delay in between pulses
    delay(500);
  }
}

void receiveDataFromBob() {
  int bobBasisSelection[32];
  unsigned long bobTimestamps[32];
  // Bob's basis selection and timestamps
  for (int i = 0; i < keyLength; i++) {
    bobBasisSelection[i] = esp_random() & 0x01;
  }
  // compare timestamps and basis selections
  for (int i = 0; i < keyLength; i++) {
    if (abs((long)(aliceTimestamps[i] - bobTimestamps[i])) < 50) {
      if (aliceBasisSelection[i] == bobBasisSelection[i]) {
        Serial.print("Bit ");
        Serial.print(i);
        Serial.println(" is valid and can be used for the key.");
      } else {
        Serial.print("Bit ");
        Serial.print(i);
        Serial.println(" has different basis selections and will be discarded.");
      }
    } else {
      Serial.print("Bit ");
      Serial.print(i);
      Serial.println(" has too large a time difference and will be discarded.");
    }
  }
}




