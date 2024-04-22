#include <Arduino.h>
#include <ArduinoJson.h>

#include "Motor.h"
#include "Solenoid.h"
#include "Interface.h"

// 2, 3, 18, 19, 20, 21 interrupts

unsigned long lastExecutedMillis = 0;
const unsigned long delayInterval = 1000;

Motor mix(1, 2, 3, 4, 5);
Motor mmd(1, 2, 3, 4, 5);
Motor mrl(1, 2, 3, 4, 5);
Motor mtf(1, 2, 3, 4, 5);
Motor mto(1, 2, 3, 4, 5);
Solenoid six(1, 2);
Solenoid smd(1, 2);
Hand hand(&mix, &mmd, &mrl, &mtf, &mto, &six, &smd);
Interface interface(&hand);

void setup()
{
    hand.init();
    interface.init();
}

void loop()
{
    unsigned long currentMillis = millis();
    if (currentMillis - lastExecutedMillis >= delayInterval)
    {
        lastExecutedMillis = currentMillis; // save the last executed time
        interface.update();
    }
}
