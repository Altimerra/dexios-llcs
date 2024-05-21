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
            digitalWrite(*(hand->stby1), !digitalRead(*(hand->stby1)));
            interface->print("Stby1",bool(digitalRead(*(hand->stby1))));
            break;
        case 'g':
            digitalWrite(*(hand->stby2), !digitalRead(*(hand->stby2)));
            interface->print("Stby2",digitalRead(*(hand->stby1)));
            break;
        case 'h':
            digitalWrite(*(hand->stby3), !digitalRead(*(hand->stby3)));
            interface->print("Stby3",digitalRead(*(hand->stby1)));
            break;
        case 'i':
            hand->six->toggle();
            interface->print("S Index", hand->six->state);
            break;
        case 'j':
            hand->smd->toggle();
            interface->print("S Middle", hand->smd->state);
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
            mode = Mode::PID; // TODO redundant?
            hand->setmode(Mode::PID);
            interface->print("Control Mode","PID");
            break;
        case 'p':
            mode = Mode::Manual; // TODO redundant?
            hand->setmode(Mode::Manual);
            interface->print("Control Mode","Manual");
            break;
        default:
            break;
    }

    xaxis = analogRead(vx);
    yaxis = analogRead(vy);
}

void Controller::setsetval()
{
    switch (motor)
    {
    case Motors::mix:
        hand->mix->set((xaxis-523)*10);
        break;
    case Motors::mmd:
        hand->mmd->set((xaxis-523)*10);
        break;
    default:
        break;
    }
}

void Controller::setoutspeed()
{
    switch (motor)
    {
    case Motors::mix:
        hand->mix->setspeed(map(xaxis-523,-512,512,-255,255));
        break;
    case Motors::mmd:
        hand->mmd->setspeed(map(xaxis-523,-512,512,-255,255));
        break;
    default:
        break;
    }
}



void Controller::update()
{
    chkinput();

    switch (mode)
    {
    case Mode::PID:
        setsetval();
        break;
    case Mode::Manual:
        setoutspeed();
        break;
    default:
        break;
    }
}

// TODO add solenoid support