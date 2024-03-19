#include "Interface.h"


Interface::Interface()
{
    
}


Interface::~Interface(){

}

void Interface::update()
{
    if (Serial.available() > 0)
    {
        // Read the incoming JSON data
        // String jsonInput = Serial.readStringUntil('\n');

        // Parse the JSON data
        DeserializationError error = deserializeJson(serialdata, Serial);

        // Check for parsing errors
        if (error)
        {

            serialdata["error"] = error.c_str();
            serializeJson(serialdata, Serial);
            Serial.println();
            return;
        }

        // Access the JSON data
        const char *command = serialdata["command"];
        int value = serialdata["value"];
        data["M1"] = value;

        // Process the command
        if (strcmp(command, "Mi") == 0)
        {
            currentAct = Actions::Mi;
            serialdata["status"] = "OK";
            serialdata["data"] = data["Mi"];
            serializeJson(serialdata, Serial);
            Serial.println();
            serialdata.clear();
        }
    }
}
