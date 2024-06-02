#ifndef INTER_H
#define INTER_H

#include "Common.h"
#include <ArduinoJson.h>
#include "Actuators.h"


class Interface
{
private:
    
public:
    JsonDocument serialin;
    JsonDocument serialout;
    Actuators* actuators;
    MotorValue mtrval;
    SolValue slval;
    Grasps grasp;
    Modes mode;
    Interface(Actuators*);
    ~Interface();
    void init();
    void update();
    template<typename T,typename U> void print(T key, U value);
    void print(char* key, int value);
    void periodic();
    void clear();
    void flush();
    void sendback();
};

#endif

