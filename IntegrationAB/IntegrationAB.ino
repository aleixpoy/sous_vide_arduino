#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int pinTempSensor = 8;
const int pinRelayHeater = 13;
const int pinRelayPump = 13;
const int pinSwitch = 2;
const int pinPotentiometer = A4;
const int pinYellowLED = 3;
const int pinGreenLED = 4;
const int pinRedLED = 7;

const int minTemp = 0;
const int maxTemp = 100;

float MeasuredTemperature;
float ReferenceTemperature;

boolean systemOn = false;

OneWire oneWire(pinTempSensor);
DallasTemperature sensors(&oneWire);

void control_heater(float measuredTemp, float referenceTemp) {
    if (measuredTemp < referenceTemp) {
      digitalWrite(pinRelayHeater, LOW);
    } else {
      digitalWrite(pinRelayHeater, HIGH);
    }
}

void display_LEDs_temperature(float measuredTemp, float referenceTemp) {
    if (measuredTemp < referenceTemp) {
      digitalWrite(pinYellowLED, HIGH);
      digitalWrite(pinGreenLED, LOW);
      digitalWrite(pinRedLED, LOW);
    } else if (measuredTemp >= referenceTemp &&
               measuredTemp <= referenceTemp + 2) {
      digitalWrite(pinYellowLED, LOW);
      digitalWrite(pinGreenLED, HIGH);
      digitalWrite(pinRedLED, LOW);
    } else {
      digitalWrite(pinYellowLED, LOW);
      digitalWrite(pinGreenLED, LOW);
      digitalWrite(pinRedLED, HIGH);
    }
}

float measure_temperature() {
    sensors.requestTemperatures();
    float MeasuredTemp = sensors.getTempCByIndex(0);
    return MeasuredTemp;
}

float set_reference_temperature() {
    int potValue = analogRead(pinPotentiometer);
    float ReferenceTemp = map(potValue, 0, 1023, minTemp, maxTemp);
    return ReferenceTemp;
}

void turn_off_outputs() {
    digitalWrite(pinRelayHeater, LOW);
    digitalWrite(pinRelayPump, LOW);

    digitalWrite(pinYellowLED, LOW);
    digitalWrite(pinGreenLED, LOW);
    digitalWrite(pinRedLED, LOW);
}

void loop() { 
  MeasuredTemperature = measure_temperature();
  ReferenceTemperature = set_reference_temperature();
  systemOn = digitalRead(pinSwitch);

  if (systemOn) {
    control_heater(MeasuredTemperature, ReferenceTemperature);
    display_LEDs_temperature(MeasuredTemperature, ReferenceTemperature);
  } else {
    turn_off_outputs();
  }

  delay(500);
}