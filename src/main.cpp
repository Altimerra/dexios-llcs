#include <Arduino.h>
#include <Ticker.h>

#include "Motor.h"
#include "Solenoid.h"
#include "Interface.h"
#include "Panel.h"
#include "Controller.h"

// 2, 3, 18, 19, 20, 21 interrupts
uint8_t stby1 = 37;
uint8_t stby2 = 38;
uint8_t stby3 = 50;

// unsigned long lastExecutedMillis = 0;
// const unsigned long delayInterval = 1000;

Motor mix(8, 39, 41, 3, 26, &stby1);
Motor mmd(12, 33, 35, 19, 28, &stby1);
Motor mtf(10, 36, 34, 21, 30, &stby2);
Motor mto(44, 42, 40, 20, 22, &stby2);
Motor mrl(46, 48, 47, 18, 24, &stby3);

Solenoid six(6);
Solenoid smd(4);

byte rowPins[4] = {A5, A6, A7, A8}; // connect to the row pinouts of the keypad
byte colPins[4] = {A4, A3, A2, A1}; // connect to the column pinouts of the keypad
Actuators actuators(&mix, &mmd, &mrl, &mtf, &mto, &six, &smd, &stby1, &stby2, &stby3);
Interface interface(&actuators);
Panel panel(&actuators, &interface, rowPins, colPins, A9, A10);
Controller controller(&actuators, &interface);

void periodic()
{
    interface.periodic();
    //interface.print("setpoint", actuators.mix->setpoint);
    //interface.print("mode", (int)controller.currentmode); 
    //interface.flush();
    //actuators.six->toggle();
    //actuators.smd->toggle();
}

Ticker timer(periodic, 3000);

void setup()
{
    actuators.init();
    interface.init();
    timer.start();
    //actuators.mix->set(3000);
}

void loop()
{
    interface.update();
    controller.update();
    actuators.update();
    timer.update();
    //interface.sendback();
}
