#include <Arduino.h>
#include <ArduinoJson.h>
#include "Motor.h"
#include "Solenoid.h"

// 2, 3, 18, 19, 20, 21 interrupts

JsonDocument doc;
Motor mtr(2, 3, 4, 20, 21);

unsigned long previousMillis = 0;
unsigned long delayInterval = 1000;

void setup()
{
    Serial.begin(9600);
    mtr.set(-30000);
    mtr.speedmul = 1.0;
}

void loop()
{
    mtr.update();

    unsigned long currentMillis = millis();

    // if (currentMillis - previousMillis >= delayInterval)
    //{

    if (Serial.available() > 0)
    {
        // Read the incoming JSON data
        // String jsonInput = Serial.readStringUntil('\n');

        // Parse the JSON data
        DeserializationError error = deserializeJson(doc, Serial);

        // Check for parsing errors
        if (error)
        {
            // Serial.print("Error parsing JSON: ");
            // Serial.println(error.c_str());
            doc["error"] = error.c_str();

            serializeJson(doc, Serial);
            Serial.println();
            return;
        }

        // Access the JSON data
        const char *command = doc["command"];
        int value = doc["value"];

        // Process the command
        if (strcmp(command, "LED") == 0)
        {
            // Perform actions based on the received command
            // Serial.print("Received command: ");
            // Serial.println(command);
            // Serial.print("Received value: ");
            // Serial.println(value);

            // Respond back with acknowledgment
            // StaticJsonDocument<128> response;
            doc["status"] = "OK";
            doc["message"] = "Command received successfully";

            // Serialize the response and send it back through Serial

            serializeJson(doc, Serial);
            Serial.println();

            doc.clear();
            // previousMillis = currentMillis;
        }
    }
    //}
}
