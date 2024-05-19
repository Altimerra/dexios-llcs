#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include <Encoder.h>
//#include "pio_encoder.h"
#include <QuickPID.h>

class Motor
{
public:
    uint8_t PWM; 
    uint8_t IN1;
    uint8_t IN2;
    uint8_t ENC1;
    uint8_t ENC2;
    uint8_t* stby;

    //const int interval = 20;
    double speedmul = 1.0; // 0 - 1 value speed multiplier
    //unsigned long lastUpdateTime;
    //unsigned long speedSetTime;

    void rcw(); //Driver Rotate Clockwise
    void racw(); //Driver Rotate Anti-Clockwise
    void stp(); //stop the Driver
    void ss(); //Set speed in hardware
    void dir(); //Set direction

    Encoder encoder;
    QuickPID PID;
    
    //PioEncoder encoder;
    
    Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2, uint8_t* stby);
    ~Motor();
    void init();

    bool running = false;
    float encval; // current encoder reading
    float outspeed; // PID output to PWM pin
    float setpoint = 0;
    const float p = 0.15;
    const float i = 0.1;
    const float d = 0;

    void set(int ticks);
    void update();
};

#endif