#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Encoder.h>
#include <ArduPID.h>

class Motor
{
public:
    uint8_t PWM; 
    uint8_t IN1;
    uint8_t IN2;
    uint8_t ENC1;
    uint8_t ENC2;

    //const int interval = 20;
    double speedmul = 1.0; // 0 - 1 value speed multiplier
    //unsigned long lastUpdateTime;
    //unsigned long speedSetTime;

    void rcw(); //Driver Rotate Clockwise
    void racw(); //Driver Rotate Anti-Clockwise
    void stp(); //stop the Driver
    void ss(); //Set speed in hardware
    void dir(); //Set direction

    ArduPID PID;
    Encoder encoder;
    
    Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2);
    ~Motor();
    void init();

    bool running = false;
    double encval; // current encoder reading
    double outspeed; // PID output to PWM pin
    //double target = 0; // target ticks signed value
    double setpoint = 0;
    const double p = 0.15;
    const double i = 0.0;
    const double d = 0;

    void set(int ticks);
    void update();
};

#endif