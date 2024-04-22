#include "Motor.h"

Motor::Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2) : PWM(PWM), IN1(IN1), IN2(IN2), ENC1(ENC1), ENC2(ENC2), encoder(ENC1, ENC2)
{

    PID.begin(&encval, &outspeed, &setpoint, p, i, d);

    // PID.reverse()               // Uncomment if controller output is "reversed"
    PID.setSampleTime(10); // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
    PID.setOutputLimits(-255, 255);
    // PID.setBias(0);
    PID.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up

    PID.start();
    // PID.reset();               // Used for resetting the I and D terms - only use this if you know what you're doing
    // PID.stop();                // Turn off the PID controller (compute() will not do anything until start() is called)
}

Motor::~Motor()
{
    // PID.stop();
}

void Motor::init()
{
    pinMode(PWM, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

void Motor::rcw()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void Motor::racw()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void Motor::stp()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void Motor::ss()
{
    analogWrite(PWM, abs(speedmul * outspeed));
}

void Motor::dir()
{
    if (outspeed > 0)
    {
        racw();
    }
    else if (outspeed < 0)
    {
        rcw();
    }
    else
    {
        stp();
    }
}
/*
void Motor::update(int speed)
{
    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime >= interval)
    { // Update every 20 milliseconds
        lastUpdateTime = currentTime;
        dir();
        ss();
    }
    if (currentTime - speedSetTime >= duration && speed != 0)
    {
        speed = 0;
    }
}
*/

void Motor::set(int ticks)
{
    this->setpoint = ticks;
    running = true;
}

void Motor::update()
{
    // Serial.println(newPosition);
    PID.compute();
    dir();
    ss();
    long newPosition = encoder.read();
    if (newPosition != encval)
    {
        encval = newPosition;
    }
    if (encval > setpoint)
    {
        // setpoint = 0;
        running = false;
    }
}