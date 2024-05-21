#include "Interface.h"

Interface::Interface(Hand* hand) : hand(hand)
{
}

Interface::~Interface()
{
}

void Interface::init()
{
    Serial.begin(115200);
    serialout["action"] = "init";
    serializeJson(serialout, Serial);
    Serial.println();
    serialout.clear();
}

void Interface::periodic()
{
    serialout["setpoint"] = hand->mix->setpoint;
    serialout["encval"] = hand->mix->encval;
    serialout["outspeed"] = hand->mix->outspeed;
    serializeJson(serialout, Serial);
    Serial.println();
    serialout.clear();
}

template<typename T,typename U> void Interface::print(T key, U value)
{
    serialout[key] = value;
    serializeJson(serialout, Serial);
    Serial.println();
    serialout.clear();
}

template void Interface::print<const char*,char*>(const char*,char*);
template void Interface::print<const char*,int>(const char*,int);
template void Interface::print<char*,char*>(char*,char*);
template void Interface::print<const char*,const char*>(const char*,const char*);
template void Interface::print<const char*,bool>(const char*,bool);

void Interface::update()
{
    //serialout["action"] = "loopchk";
    //serializeJson(serialout, Serial);
    //Serial.println();

    if (Serial.available() > 0)
    {
        serialout["action"] = "serialavailable";
        serializeJson(serialout, Serial);
        Serial.println();
        serialout.clear();
        // Read the incoming JSON data
        // String jsonInput = Serial.readStringUntil('\n');

        // Parse the JSON data
        DeserializationError error = deserializeJson(serialin, Serial);

        // Check for parsing errors
        if (error)
        {

            serialout["action"] = error.c_str();
            serializeJson(serialout, Serial);
            Serial.println();
            serialout.clear();
            return;
        }

        // Access the JSON data
        //const char *action = serialin["action"];

        // Process the action
        if (strcmp(serialin["action"], "setval") == 0)
        {
            serialout["action"] = "settingvals";
            serializeJson(serialout, Serial);
            Serial.println();

            if (serialin["data"]["mix"] != nullptr) {
                hand->mix->set(serialin["data"]["mix"]); 
            }
            if (serialin["data"]["mmd"] != nullptr) {
                hand->mmd->set(serialin["data"]["mmd"]); 
            }
            if (serialin["data"]["mrl"] != nullptr) {
                hand->mrl->set(serialin["data"]["mrl"]); 
            }
            if (serialin["data"]["mtf"] != nullptr) {
                hand->mtf->set(serialin["data"]["mtf"]); 
            }
            if (serialin["data"]["mto"] != nullptr) {
                hand->mto->set(serialin["data"]["mto"]); 
            }
            if (serialin["data"]["six"] != nullptr) {
                hand->six->set(serialin["data"]["six"]); 
            }
            if (serialin["data"]["smd"] != nullptr) {
                hand->smd->set(serialin["data"]["smd"]); 
            }
        }

        serialout["action"] = "response";
        serialout["data"]["mix"] = hand->mix->setpoint;
        serialout["data"]["mmd"] = hand->mmd->setpoint;
        serialout["data"]["mrl"] = hand->mrl->setpoint;
        serialout["data"]["mtf"] = hand->mtf->setpoint;
        serialout["data"]["mto"] = hand->mto->setpoint;
        serialout["data"]["six"] = hand->six->state;
        serialout["data"]["smd"] = hand->smd->state;

        serializeJson(serialout, Serial);
        Serial.println();
        serialout.clear();

    }
}
