#include "Hand.h"

Hand::Hand(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, Motor* mto, Solenoid* six, Solenoid* smd, uint8_t* stby1, uint8_t* stby2, uint8_t* stby3) : mix(mix), mmd(mmd), mrl(mrl), mtf(mtf), mto(mto), six(six), smd(smd), stby1(stby1), stby2(stby2), stby3(stby3)
{
}

Hand::~Hand()
{
}

void Hand::init()
{
    mix->init();
    mmd->init();
    mrl->init();
    mtf->init();
    mto->init();
    six->init();
    smd->init();

    pinMode(*stby1, OUTPUT);
    pinMode(*stby2, OUTPUT);
    pinMode(*stby3, OUTPUT);
    digitalWrite(*stby1, LOW);
    digitalWrite(*stby2, LOW);
    digitalWrite(*stby3, LOW);
}

void Hand::update()
{
    mix->update();
}