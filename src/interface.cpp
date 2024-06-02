#include "Interface.h"

Interface::Interface(Actuators* actuators) : actuators(actuators)
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
    serialout["mix"]["setpoint"] = actuators->mix->setpoint;
    serialout["mix"]["encval"] = actuators->mix->encval;
    serialout["mix"]["outspeed"] = actuators->mix->outspeed;
    serialout["mmd"]["setpoint"] = actuators->mmd->setpoint;
    serialout["mmd"]["encval"] = actuators->mmd->encval;
    serialout["mmd"]["outspeed"] = actuators->mmd->outspeed;
    serialout["mrl"]["setpoint"] = actuators->mrl->setpoint;
    serialout["mrl"]["encval"] = actuators->mrl->encval;
    serialout["mrl"]["outspeed"] = actuators->mrl->outspeed;
    serialout["mtf"]["setpoint"] = actuators->mtf->setpoint;
    serialout["mtf"]["encval"] = actuators->mtf->encval;
    serialout["mtf"]["outspeed"] = actuators->mtf->outspeed;
    serialout["mto"]["setpoint"] = actuators->mto->setpoint;
    serialout["mto"]["encval"] = actuators->mto->encval;
    serialout["mto"]["outspeed"] = actuators->mto->outspeed;
    serialout["six"]["state"] = actuators->six->state;
    serialout["smd"]["state"] = actuators->smd->state;
    serializeJson(serialout, Serial);
    Serial.println();
    serialout.clear();
}

template<typename T,typename U> void Interface::print(T key, U value)
{
    serialout[key] = value;
}

template void Interface::print<const char*,char*>(const char*,char*);
template void Interface::print<const char*,int>(const char*,int);
template void Interface::print<const char*,float>(const char*,float);
template void Interface::print<char*,char*>(char*,char*);
template void Interface::print<const char*,const char*>(const char*,const char*);
template void Interface::print<const char*,bool>(const char*,bool);

void Interface::flush()
{
    serializeJson(serialout, Serial);
    Serial.println();
    serialout.clear();
}

void Interface::update()
{
    //serialout["action"] = "loopchk";
    //serializeJson(serialout, Serial);
    //Serial.println();

    if (Serial.available() > 0)
    {
        //serialout["action"] = "serialavailable";
        //serializeJson(serialout, Serial);
        //Serial.println();
        //serialout.clear();
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
        // TODO simplify this to process single action using switch
        if (strcmp(serialin["action"], "setval") == 0)
        {
            //serialout["action"] = "settingvals";
            //serializeJson(serialout, Serial);
            //Serial.println();

            if (strcmp(serialin["actuator"], "mix") == 0) {
                mtrval = MotorValue(Motors::mix, serialin["val"]);
            } 
            else if (strcmp(serialin["actuator"], "mmd") == 0)
            {
                mtrval = MotorValue(Motors::mmd, serialin["val"]);
            }
            else if (strcmp(serialin["actuator"], "mrl") == 0)
            {
                mtrval = MotorValue(Motors::mrl, serialin["val"]);
            }
            else if (strcmp(serialin["actuator"], "mtf") == 0)
            {
                mtrval = MotorValue(Motors::mtf, serialin["val"]);
            }
            else if (strcmp(serialin["actuator"], "mto") == 0)
            {
                mtrval = MotorValue(Motors::mto, serialin["val"]);
            }
            else if (strcmp(serialin["actuator"], "six") == 0)
            {
                slval = SolValue(Solenoids::six, serialin["val"]);
            }
            else if (strcmp(serialin["actuator"], "smd") == 0)
            {
                slval = SolValue(Solenoids::smd, serialin["val"]);
            }
            else 
            {
                mtrval = MotorValue(Motors::none, 0);
                slval = SolValue(Solenoids::none, 0);
            }
        }
        else if (strcmp(serialin["action"], "modesel") == 0)
        {
            if (strcmp(serialin["val"], "pid") == 0) {
                mode = Modes::PID;
            } 
            else if (strcmp(serialin["val"], "manual") == 0)
            {
                mode = Modes::Manual;
            }
            else
            {
                mode = Modes::none;
            }
        }
        else if (strcmp(serialin["action"], "graspsel") == 0)
        {
            if (strcmp(serialin["val"], "pinch") == 0) {
                grasp = Grasps::Pinch;
            } 
            else if (strcmp(serialin["val"], "spherical") == 0)
            {
                grasp = Grasps::Spherical;
            }
            else
            {
                grasp = Grasps::none;
            }
        }
        else
        {
        }
    }
}

void Interface::sendback()
{
    if (Serial.available() > 0)
    {
        deserializeJson(serialin, Serial);
        delay(10);
        serializeJson(serialin, Serial);
        Serial.println();
        serialin.clear();
    }
}