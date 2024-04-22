#include "Interface.h"

Interface::Interface(Hand* hand) : hand(hand)
{

}

Interface::~Interface()
{
}

void Interface::init()
{
    Serial.begin(9600);
}

void Interface::update()
{
    if (Serial.available() > 0)
    {
        // Read the incoming JSON data
        // String jsonInput = Serial.readStringUntil('\n');

        // Parse the JSON data
        DeserializationError error = deserializeJson(serialin, Serial);

        // Check for parsing errors
        if (error)
        {

            serialout["action"] = error.c_str();
            serializeJson(serialout, Serial);
            return;
        }

        // Access the JSON data
        //const char *action = serialin["action"];

        // Process the action
        if (strcmp(serialin["action"], "setvalues") == 0)
        {
            if (strcmp(serialin["set"]["mix"], "true") == 0) {
                hand->mix->set(serialin["data"]["mix"]); 
            }
            if (strcmp(serialin["set"]["mmd"], "true") == 0) {
                hand->mmd->set(serialin["data"]["mmd"]); 
            }
            if (strcmp(serialin["set"]["mrl"], "true") == 0) {
                hand->mrl->set(serialin["data"]["mrl"]); 
            }
            if (strcmp(serialin["set"]["mtf"], "true") == 0) {
                hand->mtf->set(serialin["data"]["mtf"]); 
            }
            if (strcmp(serialin["set"]["mto"], "true") == 0) {
                hand->mto->set(serialin["data"]["mto"]); 
            }
            if (strcmp(serialin["set"]["six"], "true") == 0) {
                hand->six->set(serialin["data"]["six"]); 
            }
            if (strcmp(serialin["set"]["smd"], "true") == 0) {
                hand->smd->set(serialin["data"]["smd"]); 
            }
        }

        serialout["action"] = "response";
        serialout["data"]["min"] = hand->mix->encval;
        serialout["data"]["mmd"] = hand->mmd->encval;
        serialout["data"]["mrl"] = hand->mrl->encval;
        serialout["data"]["mtf"] = hand->mtf->encval;
        serialout["data"]["mto"] = hand->mto->encval;
        serialout["data"]["six"] = hand->six->state;
        serialout["data"]["smd"] = hand->smd->state;

        serializeJson(serialout, Serial);

    }
}
