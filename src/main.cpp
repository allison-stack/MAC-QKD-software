#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include "bootloader_random.h"
#define LED 2

// variable and function definitions go up here
bool isConnected = false;
int keyLength = 5;
int aliceBasisSelection[10] = {0, 1, 1, 0, 0, 0, 1, 0, 1, 0};  // Array to store basis selections
int bobBasisSelection[10] = {0, 1, 0, 1, 1, 0, 1, 0, 0, 0};
unsigned long aliceTimestamps[10] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45};  // Array to store timestamps
unsigned long bobTimestamps[10] = {0, 6, 15, 20, 23, 30, 40, 45, 50, 60};
//Above to enable entropy to get true random numbers
// bootloader_random_enable()

//Disable the entropy added to system
// bootloader_random_disable()

void receiveDataFromBob();

void setup() {
    receiveDataFromBob();

}


void loop() {
}


void receiveDataFromBob() {
    // int bobBasisSelection[32];
    // unsigned long bobTimestamps[32];
    // Bob's basis selection and timestamps
    // for (int i = 0; i < keyLength; i++) {
    //   bobBasisSelection[i] = esp_random() & 0x01;
    // }
    
    // compare timestamps and basis selections
    int i = 0;
    int j = 0;
    while (aliceTimestamps[i]) {
      while (bobTimestamps[j]){
        if (abs((long)(aliceTimestamps[i] - bobTimestamps[j])) <= 1) {
          if (aliceBasisSelection[i] == bobBasisSelection[j]) {
            Serial.print("Bit ");
            Serial.print(i);
            Serial.println(" is valid and can be used for the key.");
          } else {
            Serial.print("Bit ");
            Serial.print(i);
            Serial.println(" has different basis selections and will be discarded.");
          }
        }
        j++;
      }
      i++;
    }
}