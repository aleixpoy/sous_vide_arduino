// LCD
#include "rgb_lcd.h"

rgb_lcd lcd;

const int pinTempSensor = 8;
float SimulatedMeasuredTemperature = 0.0;
float SimulatedReferenceTemperature = 0.0;

void setup()
{
    lcd.begin(16, 2);
    lcd.setPWM(REG_RED, 0);
    lcd.setPWM(REG_GREEN, 0);
    lcd.setPWM(REG_BLUE, 0);
}

void updateLCD(float measuredTemp, float referenceTemp) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor = ");
    lcd.setCursor(9, 0);
    lcd.print(measuredTemp);
    lcd.setCursor(14, 0);
    lcd.print(" C");
    
    lcd.setCursor(0, 1);
    lcd.print("Refern = ");
    lcd.setCursor(9, 1);
    lcd.print(referenceTemp);
    lcd.setCursor(14, 1);
    lcd.print(" C");
}

void loop()
{
    for (int i = 90; i <= 105; i++) {
        SimulatedMeasuredTemperature = i;
        SimulatedReferenceTemperature = i+5;
        updateLCD(SimulatedMeasuredTemperature, SimulatedReferenceTemperature);
        delay(1000);
    }
}
