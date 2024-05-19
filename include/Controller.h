#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>
#include <Keypad.h>
#include "Interface.h"
#include "Hand.h"

class Controller
{
private:
    char keys[4][4] = {
        {'a','b','c','d'},
        {'e','f','g','h'},
        {'i','j','k','l'},
        {'m','n','o','p'},
    };
    enum class Mode {Manual, PID};
    enum class Motors {mix, mmd};
public:
    Keypad keypad;
    uint8_t vx;
    uint8_t vy;
    int xaxis;
    int yaxis;
    Mode mode; //current mode
    Motors motor; //current motor
    Hand* hand;
    Interface* interface;
    Controller(Hand* hand, Interface* interface, byte rowPins[4], byte colPins[4], uint8_t vx, uint8_t vy);
    ~Controller();
    void chkinput();
    void update();
    void setvalues();
    void init();
};



//TODO add Manual and PID based control selector
//TODO add tuning controls
#endif