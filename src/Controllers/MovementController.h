#pragma once
#include <Arduino.h>
#include "../Drivers/MotorDriver.h"
#include "../Drivers/SwitchDriver.h"

class MovementController {
public:
    MovementController(MotorDriver& motors, SwitchDriver& switches);

    void begin();
    void loop();

    void enterStop();
    void setTurnRange(uint16_t minMs, uint16_t maxMs) {
        _turnMin = minMs;
        _turnMax = maxMs;
    }
    
    MotorDriver& getMotorDriver() { return _motors; } 

private:
    MotorDriver& _motors;
    SwitchDriver& _switches;
    

    enum State {
        DRIVING,
        BACKING_UP,
        TURNING
    };

    State _state = DRIVING;

    unsigned long _stateStart = 0;
    unsigned long _turnDuration = 0;
    bool _turnLeft = true;

    uint16_t _turnMin = 200;
    uint16_t _turnMax = 600;

    void enterState(State s);
};
