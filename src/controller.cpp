#include "Controller.h"

Controller::Controller(Actuators* actuators, Interface* interface): actuators(actuators), interface(interface), currentgrasp(Grasps::none), currentmode(Modes::PID)
{
}

Controller::~Controller()
{
}

void Controller::update()
{
    auto mode = interface->mode;
    auto mtrval = interface->mtrval;
    auto slval = interface->slval;
    auto grasp = interface->grasp;


    // TODO if mode changes from current mode update all motors
    if (mode != currentmode)
    {
        currentmode = mode;
        actuators->setmode(currentmode);
    }

    switch (currentmode)
    {
    case Modes::PID:
        setsetpoint(mtrval);
        break;
    case Modes::Manual:
        setoutspeed(mtrval);
        break;
    default:
        break;
    }

    setsolval(slval);
    
}

void Controller::setgrasp(Grasps grasp, float factor)
{
    currentgrasp = grasp;
    actuators->mix->set( int(trunc(factor*range[0])) );
    actuators->mmd->set( int(trunc(factor*range[1])) );
    actuators->mrl->set( int(trunc(factor*range[2])) );
    actuators->mtf->set( int(trunc(factor*range[3])) );
    actuators->mto->set( int(trunc(factor*range[4])) );
}

void Controller::chkgraspprog() // control solenoids while grasping
{
    switch (currentgrasp)
    {
    case Grasps::Spherical:
        if (actuators->mix->encval > grasp_spherical[0][0]) {
            actuators->six->on();  
        }
        if (actuators->mix->encval > grasp_spherical[0][1]) {
            actuators->six->off();
        }
        if (actuators->mmd->encval > grasp_spherical[1][0]) {
            actuators->smd->on();  
        }
        if (actuators->mmd->encval > grasp_spherical[1][1]) {
            actuators->smd->off();
        }
        break;
    case Grasps::Pinch:
        if (actuators->mix->encval > grasp_precision[0][0]) {
            actuators->six->on();  
        }
        if (actuators->mix->encval > grasp_precision[0][1]) {
            actuators->six->off();
        }
        if (actuators->mmd->encval > grasp_precision[1][0]) {
            actuators->smd->on();  
        }
        if (actuators->mmd->encval > grasp_precision[1][1]) {
            actuators->smd->off();
        }
        break;
        break;
    default:
        break;
    }
}

void Controller::setsetpoint(MotorValue mtr)
{
    switch (mtr.motor)
    {
    case Motors::mix:
        actuators->mix->set(mtr.value);
        break;
    case Motors::mmd:
        actuators->mmd->set(mtr.value);
        break;
    case Motors::mrl:
        actuators->mrl->set(mtr.value);
        break;
    case Motors::mtf:
        actuators->mtf->set(mtr.value);
        break;
    case Motors::mto:
        actuators->mto->set(mtr.value);
        break;
    default:
        break;
    }
}

void Controller::setoutspeed(MotorValue mtr)
{
    switch (mtr.motor)
    {
    case Motors::mix:
        actuators->mix->setspeed(mtr.value);
        break;
    case Motors::mmd:
        actuators->mmd->setspeed(mtr.value);
        break;
    case Motors::mrl:
        actuators->mrl->setspeed(mtr.value);
        break;
    case Motors::mtf:
        actuators->mtf->setspeed(mtr.value);
        break;
    case Motors::mto:
        actuators->mto->setspeed(mtr.value);
        break;
    default:
        break;
    }
}

void Controller::setsolval(SolValue sol)
{
    switch (sol.solenoid)
    {
    case Solenoids::six:
        actuators->six->set(sol.value);
        break;
    case Solenoids::smd:
        actuators->smd->set(sol.value);
        break;
    default:
        break;
    }
}