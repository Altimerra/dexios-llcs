#include "Motor.h"

Motor::Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2, uint8_t*stby) : PWM(PWM), IN1(IN1), IN2(IN2), ENC1(ENC1), ENC2(ENC2), encoder(ENC1,ENC2), stby(stby), PID(&encval,&outspeed,&setpoint)
{
    PID.SetTunings(p, i, d);
    PID.SetOutputLimits(-255, 255);
    PID.SetMode(QuickPID::Control::automatic);
    // TODO check motor driver direction pins with the diagram
    // TODO tune pid
    // PID.reverse()               // Uncomment if controller output is "reversed"
    //PID.setSampleTime(10); // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
    
    // PID.setBias(0);
    //PID.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up

    //PID.start();
    // PID.reset();               // Used for resetting the I and D terms - only use this if you know what you're doing
    // PID.stop();                // Turn off the PID controller (compute() will not do anything until start() is called)
    //encoder.begin();
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
    //float speed = (abs(outspeed) < 50) ? 50 : abs(outspeed);
    float speed =  abs(outspeed);
    analogWrite(PWM, speed);
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
}

void Motor::update()
{
    // Serial.println(newPosition);
    if (!digitalRead(*stby))
    {
        digitalWrite(*stby, HIGH);
    }
    PID.Compute();
    dir();
    ss();
    long newPosition = encoder.read();
    //long newPosition = encoder.getCount();
    if (newPosition != encval)
    {
        encval = newPosition;
    }
}

//should work in both pid and non pid modes in case encoder fails