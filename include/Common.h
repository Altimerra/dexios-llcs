#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

enum class Motors {mix, mmd, mrl, mtf, mto, six, smd, none};
enum class Solenoids {six, smd, none};
enum class Modes {PID, Manual, none};
enum class Grasps {Pinch, Spherical, none};

struct MotorValue
{
    Motors motor;
    int value;
    MotorValue(): motor(Motors::none), value(0) {};
    MotorValue(Motors m,int v): motor(m), value(v) {};
};

struct SolValue
{
    Solenoids solenoid;
    bool value;
    SolValue(): solenoid(Solenoids::none), value(0) {};
    SolValue(Solenoids s,int v): solenoid(s), value(v) {};
};

#endif