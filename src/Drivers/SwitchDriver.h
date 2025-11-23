#pragma once
#include <Arduino.h>
#include "../Config.h"

class SwitchDriver {
public:
    void begin() {
        pinMode(PIN_SWITCH, INPUT_PULLUP);
    }

    bool collision() {
        return digitalRead(PIN_SWITCH) == LOW;
    }

};
