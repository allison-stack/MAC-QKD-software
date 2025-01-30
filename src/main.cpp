#include <Arduino.h>

// put function declarations here:
int BlueLedPin = 2;

void LaserPulse(int pin, int HighTime, int LowTime){
  digitalWrite(pin, HIGH);
  delay(HighTime);
  digitalWrite(pin, LOW);
  delay(LowTime);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Program");
  pinMode(BlueLedPin, OUTPUT);
  Serial.println("Pin Configured");
}

void loop() {
  LaserPulse(BlueLedPin, 10, 7000);
}