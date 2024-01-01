//// Abast Milestone A:
// Mesura sensor temperatura [Implementat]
// Control relé heater [Implementat]
// Control relé Bomba hidràulica [Implementat]
// Referència temperatura [Ignorat]
// Botó activació sistema [Ignorat]
// LEDs [Ignorat]
// LCD [Ignorat]


#include <OneWire.h>
#include <DallasTemperature.h>


const int pinTempSensor = 8;


const int pinRelayHeater = 13;


const int pinRelayPump = 12;


float temperature;

OneWire oneWire(pinTempSensor);
DallasTemperature sensors(&oneWire);

void setup() {
 
  Serial.begin(9600);
 
  sensors.begin();
 
  pinMode(pinRelayHeater, OUTPUT);
  pinMode(pinRelayPump, OUTPUT);
}

void loop() {

  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  Serial.print("Temperatura actual: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature < 30) {
    digitalWrite(pinRelayHeater, LOW);
  } else {
    digitalWrite(pinRelayHeater, HIGH);
  }

  delay(500);
}
