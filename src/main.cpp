#include <Arduino.h>
#include <ArduinoJson.h>

#include "Motor.h"
#include "Solenoid.h"
#include "Interface.h"

// 2, 3, 18, 19, 20, 21 interrupts

Motor mtr(2, 3, 4, 20, 21);
Solenoid sol(40, 41);
Interface interface;

unsigned long previousMillis = 0;
unsigned long delayInterval = 1000;

void setup()
{
    Serial.begin(9600);
    mtr.init();
    sol.init();
    mtr.set(3000);
    mtr.speedmul = 1.0;
}

void loop()
{
    mtr.update();
    interface.update();
    switch (interface.currentAct)
    {
    case Actions::Mi :
        // code to execute if expression == value1
        mtr.set(interface.data["Mi"]);
        interface.currentAct = Actions::None;
        break;
    }
}
