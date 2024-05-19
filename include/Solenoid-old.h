#ifndef SOLENOID_H
#define SOLENOID_H

class SolenoidOld
{
private:
    uint16_t IN1;
    uint16_t IN2;
public:
    bool state;
    SolenoidOld(uint16_t IN1, uint16_t IN2);
    ~SolenoidOld();
    void init();
    void on();
    void off();
    void set(int);
};

#endif
