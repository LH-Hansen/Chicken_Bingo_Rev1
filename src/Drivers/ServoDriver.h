#pragma once
#include <Arduino.h>
#include <Servo.h>

class ServoDriver {
public:
    void begin(uint8_t pin);
    void open();
    void close();
    void detach();

private:
    Servo _servo;
    uint8_t _pin = 0;

    uint8_t _openAngle  = 130;
    uint8_t _closeAngle = 5;
};
