#include <Arduino.h>
#include "Solenoid.h"

Solenoid::Solenoid(uint16_t IN) : IN(IN)
{
}

Solenoid::~Solenoid()
{
}

void Solenoid::init()
{
    pinMode(IN, OUTPUT);
    state = false;
}

void Solenoid::on()
{
    digitalWrite(IN, HIGH);
    state = true;
}

void Solenoid::off()
{
    digitalWrite(IN, LOW);
    state = false;
}

void Solenoid::set(int state)
{
    if (state) {
        this->on();
    } else {
        this->off();
    }
}