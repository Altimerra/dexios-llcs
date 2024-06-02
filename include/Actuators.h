#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "Common.h"
#include <Motor.h>
#include <Solenoid.h>

class Actuators
{
private:
    /* data */
public:
    Actuators(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, 
        Motor* mto, Solenoid* six, Solenoid* smd,
        uint8_t* stby1, uint8_t* stby2, uint8_t* stby3);
    ~Actuators();
    void init();
    void update();
    void setmode(Modes mode);
    Motor* mix;
    Motor* mmd;
    Motor* mrl;
    Motor* mtf;
    Motor* mto;
    Solenoid* six;
    Solenoid* smd;
    uint8_t* stby1;
    uint8_t* stby2;
    uint8_t* stby3;
};
#endif