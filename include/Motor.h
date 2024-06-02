#ifndef MOTOR_H
#define MOTOR_H

#include "Common.h"
#include <Encoder.h>
#include <QuickPID.h>
#include <sTune.h>


class Motor
{
private:
    const uint8_t relayPin = 8;
    uint32_t settleTimeSec = 10;
    uint32_t testTimeSec = 500; // runPid interval = testTimeSec / samples
    const uint16_t samples = 500;
    const float inputSpan = 12000;
    const float outputSpan = 255;
    float outputStart = 0;
    float outputStep = 50;
    float tempLimit = 1500;
    uint8_t debounce = 1;

public:
    uint8_t PWM;
    uint8_t IN1;
    uint8_t IN2;
    uint8_t ENC1;
    uint8_t ENC2;
    uint8_t *stby;

    // const int interval = 20;
    double speedmul = 1.0; // 0 - 1 value speed multiplier
    // unsigned long lastUpdateTime;
    // unsigned long speedSetTime;

    void rcw();  // Driver Rotate Clockwise
    void racw(); // Driver Rotate Anti-Clockwise
    void stp();  // stop the Driver
    void ss();   // Set speed in hardware
    void dir();  // Set direction

    Encoder encoder;
    QuickPID PID;
    sTune tuner;
    Modes mode;

    Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2, uint8_t *stby);
    ~Motor();
    void init();

    bool running = false;
    float encval;   // current encoder reading
    float outspeed; // PID output to PWM pin
    float setpoint = 0;
    float p = 0.15;
    float i = 0.1;
    float d = 0;

    void set(int ticks); // For pid control
    void setspeed(int speed); // For manual control
    void update();
    void tune();
};

#endif