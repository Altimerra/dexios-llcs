#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder(uint8_t EPIN1, uint8_t EPIN2, uint8_t INTRPT): EPIN1(EPIN1), EPIN2(EPIN2)
{
    pinMode(EPIN1, INPUT_PULLUP); 
    pinMode(EPIN2, INPUT_PULLUP);

    digitalWrite(EPIN1, HIGH); //turn pullup resistor on
    digitalWrite(EPIN2, HIGH); //turn pullup resistor on
}

Encoder::~Encoder()
{
}

void Encoder::update()
{
  int MSB = digitalRead(EPIN1); //MSB = most significant bit
  int LSB = digitalRead(EPIN2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; //store this value for next time

}