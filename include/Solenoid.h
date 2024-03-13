#ifndef SOLENOID_H
#define SOLENOID_H

class Solenoid
{
private:
    uint16_t IN1;
    uint16_t IN2;
public:
    Solenoid(uint16_t IN1, uint16_t IN2);
    ~Solenoid();
    void on();
    void off();
};

#endif
