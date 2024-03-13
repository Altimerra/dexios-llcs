#include <Arduino.h>
#include "Driver.h"
#include "Encoder.h"
#include "Motor.h"
#include "Solenoid.h"

Driver drv(4, 24, 26);
Encoder enc(6, 7, 8); // placeholder
Motor motor(drv, enc);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    motor.driver.update();

    if (Serial.available() > 0)
    {
        // Read the incoming character
        char incomingChar = Serial.read();

        // Print the received character
        Serial.print("Received: ");
        Serial.println(incomingChar);
    }
}
