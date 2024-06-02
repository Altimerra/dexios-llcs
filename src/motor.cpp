#include "Motor.h"

Motor::Motor(uint8_t PWM, uint8_t IN1, uint8_t IN2, uint8_t ENC1, uint8_t ENC2, uint8_t*stby) : 
PWM(PWM), IN1(IN1), IN2(IN2), ENC1(ENC1), ENC2(ENC2), encoder(ENC1,ENC2), stby(stby), 
PID(&encval,&outspeed,&setpoint),
tuner(&encval, &outspeed, tuner.ZN_PID, tuner.directIP, tuner.printALL),
mode(Modes::PID)
{
    PID.SetTunings(p, i, d);
    PID.SetOutputLimits(-255, 255);
    PID.SetMode(QuickPID::Control::automatic);
    // TODO check motor driver direction pins with the diagram
    // TODO tune pid
    // PID.reverse()               // Uncomment if Panel output is "reversed"
    //PID.setSampleTime(10); // OPTIONAL - will ensure at least 10ms have past between successful compute() calls
    
    // PID.setBias(0);
    //PID.setWindUpLimits(-10, 10); // Groth bounds for the integral term to prevent integral wind-up

    //PID.start();
    // PID.reset();               // Used for resetting the I and D terms - only use this if you know what you're doing
    // PID.stop();                // Turn off the PID Panel (compute() will not do anything until start() is called)
    //encoder.begin();
}

Motor::~Motor()
{
    // PID.stop();
}

void Motor::init()
{
    pinMode(PWM, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    //tuner.Configure(inputSpan, outputSpan, outputStart, outputStep, testTimeSec, settleTimeSec, samples);
    //tuner.SetEmergencyStop(tempLimit);
    outspeed = 0;
}

void Motor::rcw()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void Motor::racw()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void Motor::stp()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void Motor::ss()
{
    //float speed = (abs(outspeed) < 50) ? 50 : abs(outspeed);
    float speed =  abs(outspeed);
    analogWrite(PWM, speed);
}

void Motor::dir()
{
    if (outspeed > 0)
    {
        racw();
    }
    else if (outspeed < 0)
    {
        rcw();
    }
    else
    {
        stp();
    }
}

void Motor::set(int ticks)
{
    setpoint = float(ticks);
}

void Motor::update()
{
    /* NOTE there is probably a better way to check this
    if (!digitalRead(*stby))
    {
        digitalWrite(*stby, HIGH);
    }*/

    if (mode == Modes::PID)
    {
        PID.Compute();
    }
    
    dir();
    ss();
    encval = encoder.read();
}

void Motor::setspeed(int speed)
{
    this->outspeed = constrain(speed, -255, 255);
}

// TODO should work in both pid and non pid modes in case encoder fails
void Motor::tune()
{
    float optimumOutput = tuner.softPwm(PWM, encval, outspeed, setpoint, outputSpan, debounce);

    switch (tuner.Run())
    {
    case tuner.sample: // active once per sample during test
        encval = encoder.read();
        tuner.plotter(encval, outspeed, setpoint, 0.5f, 3); // output scale 0.5, plot every 3rd sample
        break;

    case tuner.tunings:                      // active just once when sTune is done
        tuner.GetAutoTunings(&p, &i, &d); // sketch variables updated by sTune
        PID.SetOutputLimits(0, outputSpan * 0.1);
        PID.SetSampleTimeUs((outputSpan - 1) * 1000);
        debounce = 0; // ssr mode
        outspeed = outputStep;
        PID.SetMode(QuickPID::Control::automatic); // the PID is turned on
        PID.SetProportionalMode(QuickPID::pMode::pOnMeas);
        PID.SetAntiWindupMode(QuickPID::iAwMode::iAwClamp);
        PID.SetTunings(p, i, d); // update PID with the new tunings
        break;

    case tuner.runPid: // active once per sample after tunings
        encval = encoder.read();
        PID.Compute();
        tuner.plotter(encval, optimumOutput, setpoint, 0.5f, 3);
        break;
    }
}