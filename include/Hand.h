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
    Hand(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, Motor* mto, Solenoid* six, Solenoid* smd);
    ~Hand();
    void init();
    Motor* mix;
    Motor* mmd;
    Motor* mrl;
    Motor* mtf;
    Motor* mto;
    Solenoid* six;
    Solenoid* smd;
};
#endif