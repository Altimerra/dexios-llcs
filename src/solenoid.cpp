#include <Arduino.h>
#include "Solenoid.h"

Solenoid::Solenoid(uint16_t IN1, uint16_t IN2)
{
    this->IN1 = IN1;
    this->IN2 = IN2;
}

Solenoid::~Solenoid()
{
}

void Solenoid::init()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

void Solenoid::on()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void Solenoid::off()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}