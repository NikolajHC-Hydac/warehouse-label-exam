#include <Arduino.h>

#define INPUT_PIN A0

const int numReadings = 10;
const int deviation = 50;

int readButton();
int oldResult;
bool buttonState;
int readings = 0;
int total = 0;
int average = 0;
int readingCheck = 0;
int oldReadingCheck = 0;

void setup() {
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  buttonState = false;
}

void loop() {
  
  int result = readButton();
  delay(100);
  if (result != 0 && !buttonState){
    Serial.print(result);
    Serial.print(" ");
    Serial.println(average);
    oldResult = result;
    buttonState = true;
  }
}

int readButton() {
  readingCheck = analogRead(INPUT_PIN);
  if (abs(oldReadingCheck - readingCheck) > deviation){
    for (readings = 0; readings <= numReadings; readings++){
      total = total + analogRead(INPUT_PIN);
    }
    average = total / readings;
    total = 0;
    oldReadingCheck = readingCheck;
    if (average > 900){
      total = 0;
      buttonState = false;
      return 0;
    }
    if (average == 0) return 1;
    if (average < 100) return 2;
    if (average < 270) return 3;
    if (average < 433) return 4;
    if (average < 582) return 5;
    if (average < 720) return 6;
    if (average < 900) return 7;
  }
}