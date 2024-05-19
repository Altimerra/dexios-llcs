#ifndef HAND_H
#define HAND_H
#include <Arduino.h>
#include <Motor.h>
#include <Solenoid.h>

class Hand
{
private:
    /* data */
public:
    Hand(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, 
        Motor* mto, Solenoid* six, Solenoid* smd,
        uint8_t* stby1, uint8_t* stby2, uint8_t* stby3);
    ~Hand();
    void init();
    void update();
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