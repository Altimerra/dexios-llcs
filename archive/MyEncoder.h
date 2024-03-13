#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
private:
    uint8_t EPIN1; //encoder pin 1
    uint8_t EPIN2; //encoder pin 1
    uint8_t INTRPT; //interrupt pin
    void update();

    volatile int lastEncoded = 0; // Here updated value of encoder store.
    volatile long encoderValue = 0; // Raw encoder value
public:
    Encoder(uint8_t EPIN1, uint8_t EPIN2, uint8_t INTRPT);
    ~Encoder();
};

#endif