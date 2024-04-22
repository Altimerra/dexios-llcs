#ifndef SOLENOID_H
#define SOLENOID_H

class Solenoid
{
private:
    uint16_t IN1;
    uint16_t IN2;
public:
    bool state;
    Solenoid(uint16_t IN1, uint16_t IN2);
    ~Solenoid();
    void init();
    void on();
    void off();
    void set(int);
};

#endif
