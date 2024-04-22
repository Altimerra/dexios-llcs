#include <Arduino.h>
#include "Solenoid.h"

Solenoid::Solenoid(uint16_t IN1, uint16_t IN2) : IN1(IN1), IN2(IN2)
{
}

Solenoid::~Solenoid()
{
}

void Solenoid::init()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    state = false;
}

void Solenoid::on()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    state = true;
}

void Solenoid::off()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
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