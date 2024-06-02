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
}

void Solenoid::off()
{
    digitalWrite(IN, LOW);
}

void Solenoid::toggle()
{
    state = !state;
}

void Solenoid::set(bool state)
{
    this->state = state;
}

void Solenoid::update()
{
    if (state) {
        this->on();
    } else {
        this->off();
    }
}