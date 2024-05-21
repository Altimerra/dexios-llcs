#ifndef SOLENOID_H
#define SOLENOID_H

class Solenoid
{
private:
    uint16_t IN;
public:
    bool state;
    Solenoid(uint16_t IN);
    ~Solenoid();
    void init();
    void on();
    void off();
    void set(bool state);
    void update();
    void toggle();
};

#endif
