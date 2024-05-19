#include <Arduino.h>
#include "Solenoid-old.h"

SolenoidOld::SolenoidOld(uint16_t IN1, uint16_t IN2) : IN1(IN1), IN2(IN2)
{
}

SolenoidOld::~SolenoidOld()
{
}

void SolenoidOld::init()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    state = false;
}

void SolenoidOld::on()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    state = true;
}

void SolenoidOld::off()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    state = false;
}

void SolenoidOld::set(int state)
{
    if (state) {
        this->on();
    } else {
        this->off();
    }
}