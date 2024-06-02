#ifndef PANEL_H
#define PANEL_H

#include "Common.h"
#include <Keypad.h>
#include "Interface.h"
#include "Actuators.h"

class Panel
{
private:
    char keys[4][4] = {
        {'a','b','c','d'},
        {'e','f','g','h'},
        {'i','j','k','l'},
        {'m','n','o','p'},
    };
    
public:
    Keypad keypad;
    uint8_t vx;
    uint8_t vy;
    int xaxis;
    int yaxis;
    Modes mode; //current mode
    Motors motor; //current motor
    Actuators* actuators;
    Interface* interface;
    Panel(Actuators* actuators, Interface* interface, byte rowPins[4], byte colPins[4], uint8_t vx, uint8_t vy);
    ~Panel();
    void chkinput();
    void update();
    void setsetval();
    void setoutspeed();
    void init();
};



//TODO add Manual and PID based control selector
//TODO add tuning controls
#endif