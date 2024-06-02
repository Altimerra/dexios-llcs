#include "Panel.h"

Panel::Panel(Actuators* actuators, Interface* interface, byte rowPins[4], byte colPins[4], uint8_t vx, uint8_t vy): 
actuators(actuators), interface(interface),
keypad( makeKeymap(keys), rowPins, colPins, 4, 4 ), vx(vx), vy(vy)
{
    mode = Modes::PID;
    xaxis = 0;
    yaxis = 0;
}

Panel::~Panel()
{
}

void Panel::init()
{
    //pinMode(A0, INPUT);
    pinMode(vx, INPUT);
    pinMode(vy, INPUT);
}

void Panel::chkinput()
{
    char key = keypad.getKey();
    if (key) {
        interface->print("Keypress", &key);
    }

    switch (key) {
        case 'a':
            motor = Motors::mix;
            interface->print("Controlling Motor","M Index");
            break;
        case 'b':
            motor = Motors::mmd;
            interface->print("Controlling Motor","M Middle");
            break;
        case 'c':
            break;
        case 'd':
            break;
        case 'e':
            break;
        case 'f':
            digitalWrite(*(actuators->stby1), !digitalRead(*(actuators->stby1)));
            interface->print("Stby1",bool(digitalRead(*(actuators->stby1))));
            break;
        case 'g':
            digitalWrite(*(actuators->stby2), !digitalRead(*(actuators->stby2)));
            interface->print("Stby2",digitalRead(*(actuators->stby1)));
            break;
        case 'h':
            digitalWrite(*(actuators->stby3), !digitalRead(*(actuators->stby3)));
            interface->print("Stby3",digitalRead(*(actuators->stby1)));
            break;
        case 'i':
            actuators->six->toggle();
            interface->print("S Index", actuators->six->state);
            break;
        case 'j':
            actuators->smd->toggle();
            interface->print("S Middle", actuators->smd->state);
            break;
        case 'k':
            break;
        case 'l':
            break;
        case 'm':
            break;
        case 'n':
            break;
        case 'o':
            mode = Modes::PID; // TODO redundant?
            actuators->setmode(Modes::PID);
            interface->print("Control Modes","PID");
            break;
        case 'p':
            mode = Modes::Manual; // TODO redundant?
            actuators->setmode(Modes::Manual);
            interface->print("Control Modes","Manual");
            break;
        default:
            break;
    }

    xaxis = analogRead(vx);
    yaxis = analogRead(vy);
}

void Panel::setsetval()
{
    switch (motor)
    {
    case Motors::mix:
        actuators->mix->set((xaxis-523)*10);
        break;
    case Motors::mmd:
        actuators->mmd->set((xaxis-523)*10);
        break;
    default:
        break;
    }
}

void Panel::setoutspeed()
{
    switch (motor)
    {
    case Motors::mix:
        actuators->mix->setspeed(map(xaxis-523,-512,512,-255,255));
        break;
    case Motors::mmd:
        actuators->mmd->setspeed(map(xaxis-523,-512,512,-255,255));
        break;
    default:
        break;
    }
}



void Panel::update()
{
    chkinput();

    switch (mode)
    {
    case Modes::PID:
        setsetval();
        break;
    case Modes::Manual:
        setoutspeed();
        break;
    default:
        break;
    }
}

// TODO add solenoid support