#ifndef INTER_H
#define INTER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Hand.h"


class Interface
{
private:
    
public:
    JsonDocument serialin;
    JsonDocument serialout;
    Hand* hand;
    Interface(Hand*);
    ~Interface();
    void init();
    void update();
    void print(char* key, char* value);
    void print(char* key, int value);
    void periodic();
    void clear();
    
};

#endif

