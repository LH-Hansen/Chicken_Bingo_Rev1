#pragma once
#include <Arduino.h>
#include "../Config.h"

class MotorDriver {
public:
    void begin() {
        pinMode(PIN_IN1, OUTPUT);
        pinMode(PIN_IN2, OUTPUT);
        pinMode(PIN_IN3, OUTPUT);
        pinMode(PIN_IN4, OUTPUT);

        stopAll();
    }

    void forward() {
        motorA(HIGH, LOW);
        motorB(HIGH, LOW);
    }

    void backward() {
        motorA(LOW, HIGH);
        motorB(LOW, HIGH);
    }

    void turnLeft() {
        motorA(LOW, HIGH);
        motorB(HIGH, LOW);
    }

    void turnRight() {
        motorA(HIGH, LOW);
        motorB(LOW, HIGH);
    }

    void stopAll() {
        motorA(LOW, LOW);
        motorB(LOW, LOW);
    }


private:
    void motorA(bool a1, bool a2) {
        digitalWrite(PIN_IN1, a1);
        digitalWrite(PIN_IN2, a2);
    }

    void motorB(bool b1, bool b2) {
        digitalWrite(PIN_IN3, b1);
        digitalWrite(PIN_IN4, b2);
    }
};