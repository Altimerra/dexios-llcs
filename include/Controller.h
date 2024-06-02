#ifndef CONTROL_H
#define CONTROL_H

#include "Common.h"
#include "Actuators.h"
#include "Interface.h"

class Controller
{
private:
    // determines the points at which the solenoid is turned on and off 
    const int grasp_precision[2][2] = {{1000,2000},{300,4000}};
    const int grasp_spherical[2][2] = {{1000,2000},{3000,4000}};
    // first layer: which solenoid, second layer: on and off time
    const int range[5] = {12000, 12000, 10000, 3000, 10000};
public:
    Actuators* actuators;
    Interface* interface;
    Grasps currentgrasp;
    Modes currentmode;
    Controller(Actuators* actuators, Interface* interface);
    ~Controller();
    void update();
    void setgrasp(Grasps grasp, float factor);
    void chkgraspprog();
    void setsetpoint(MotorValue mtr);
    void setoutspeed(MotorValue mtr);
    void setsolval(SolValue sol);
};


#endif