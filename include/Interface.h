#ifndef INTER_H
#define INTER_H

#include <Arduino.h>
#include <ArduinoJson.h>

enum class Actions 
{
    Mi,
    None,
};


class Interface
{
private:
    JsonDocument serialdata;
public:
    Actions currentAct;
    JsonDocument data;
    Interface(/* args */);
    ~Interface();
    void update();
    void clear();
    
};

#endif

