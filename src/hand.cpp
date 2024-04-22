#include "Hand.h"

Hand::Hand(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, Motor* mto, Solenoid* six, Solenoid* smd) : mix(mix), mmd(mmd), mrl(mrl), mtf(mtf), mto(mto), six(six), smd(smd)
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
}