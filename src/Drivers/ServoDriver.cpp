#include "ServoDriver.h"

void ServoDriver::begin(uint8_t pin) {
    _pin = pin;
    _servo.attach(pin);
    close();
}

void ServoDriver::open() {
    _servo.attach(_pin);
    _servo.write(_openAngle);
    delay(300);               
    _servo.detach();       
}

void ServoDriver::close() {
    _servo.attach(_pin);
    _servo.write(_closeAngle);
    delay(300);
    _servo.detach();
}

void ServoDriver::detach() {
    _servo.detach();
}
