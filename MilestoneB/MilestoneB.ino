// Onjectius Milestone B:
// Activació LEDs
// ...


#include <Arduino.h>

const int pinPotentiometer = A4;  
const int pinSwitch = 2;          
const int pinYellowLED = 3;
const int pinGreenLED = 4;
const int pinRedLED = 7;

float simulatedMeasuredTemperature = 0.0;
float referenceTemperature = 0.0;
boolean systemOn = false;

void setup() {
  pinMode(pinPotentiometer, INPUT);
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinYellowLED, OUTPUT);
  pinMode(pinGreenLED, OUTPUT);
  pinMode(pinRedLED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(pinPotentiometer);

  referenceTemperature = map(potValue, 0, 1023, 0, 100);

  systemOn = digitalRead(pinSwitch);
  if (systemOn == true) {
    Serial.print("Temperatura Referencia: ");
    Serial.print(referenceTemperature);
    Serial.println(" °C");
  
    if (referenceTemperature < 49) {
      digitalWrite(pinYellowLED, HIGH);
      digitalWrite(pinGreenLED, LOW);
      digitalWrite(pinRedLED, LOW);
    } else if (referenceTemperature >= 50 && referenceTemperature <= 55) {
      digitalWrite(pinYellowLED, LOW);
      digitalWrite(pinGreenLED, HIGH);
      digitalWrite(pinRedLED, LOW);
    } else {
      digitalWrite(pinYellowLED, LOW);
      digitalWrite(pinGreenLED, LOW);
      digitalWrite(pinRedLED, HIGH);
    }
  }
  else {
    digitalWrite(pinYellowLED, LOW);
    digitalWrite(pinGreenLED, LOW);
    digitalWrite(pinRedLED, LOW);
  }

  delay(500);
}
