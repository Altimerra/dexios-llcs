#include "Controller.h"

Controller::Controller(Hand* hand, Interface* interface, byte rowPins[4], byte colPins[4], uint8_t vx, uint8_t vy): 
hand(hand), interface(interface),
keypad( makeKeymap(keys), rowPins, colPins, 4, 4 ), vx(vx), vy(vy)
{
    mode = Mode::PID;
    xaxis = 0;
    yaxis = 0;
}

Controller::~Controller()
{
}

void Controller::init()
{
    //pinMode(A0, INPUT);
    pinMode(vx, INPUT);
    pinMode(vy, INPUT);
}

void Controller::chkinput()
{
    char key = keypad.getKey();

    switch (key) {
        case 'a':
            motor = Motors::mix;
            interface->print("Controlling Motor","M Index");
            break;
        case 'b':
            motor = Motors::mmd;
            interface->print("Controlling Motor","M Middle");
            break;
        case 'p':
            mode = Mode::Manual;
            interface->print("Control Mode","Manual");
            break;
        case 'o':
            mode = Mode::PID;
            interface->print("Control Mode","PID");
            break;
        default:
            break;
    }

    xaxis = analogRead(vx);
    yaxis = analogRead(vy);
}

void Controller::setvalues()
{
    
    switch (motor)
    {
    case Motors::mix:
        hand->mix->set(xaxis*10);
        break;
    case Motors::mmd:
        hand->mmd->set(xaxis*10);
        break;
    default:
        break;
    }
}

void Controller::update()
{
    chkinput();
    if (mode == Mode::PID) {
        setvalues();
    }
}