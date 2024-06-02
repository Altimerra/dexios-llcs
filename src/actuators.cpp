#include "Actuators.h"

Actuators::Actuators(Motor* mix,  Motor* mmd, Motor* mrl, Motor* mtf, Motor* mto, Solenoid* six, Solenoid* smd, uint8_t* stby1, uint8_t* stby2, uint8_t* stby3) : mix(mix), mmd(mmd), mrl(mrl), mtf(mtf), mto(mto), six(six), smd(smd), stby1(stby1), stby2(stby2), stby3(stby3)
{
}

Actuators::~Actuators()
{
}

void Actuators::init()
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
    // TODO add control to this
    digitalWrite(*stby1, HIGH);
    digitalWrite(*stby2, HIGH);
    digitalWrite(*stby3, HIGH);
}

void Actuators::update()
{
    mix->update();
    mmd->update();
    mrl->update();
    mtf->update();
    mto->update();
    six->update();
    smd->update();
}

void Actuators::setmode(Modes mode)
{
    mix->mode = mode;
    mmd->mode = mode;
    mrl->mode = mode;
    mtf->mode = mode;
    mto->mode = mode;

}