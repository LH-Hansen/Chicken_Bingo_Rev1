#include "MovementController.h"
#include "../Config.h"

MovementController::MovementController(MotorDriver& motors, SwitchDriver& switches)
    : _motors(motors), _switches(switches)
{}

void MovementController::begin() {
    _motors.begin();
    _switches.begin();
}

void MovementController::enterStop() {
    _motors.stopAll();
    _state = DRIVING;
}

void MovementController::enterState(State s) {
    _state = s;
    _stateStart = millis();

    switch (_state) {
        case DRIVING:
            _motors.forward();
            break;

        case BACKING_UP:
            _motors.backward();
            break;

        case TURNING:
            _turnLeft = random(0, 2) == 0;
            _turnDuration = random(_turnMin, _turnMax);
            _turnLeft ? _motors.turnLeft() : _motors.turnRight();
            break;
    }
}

void MovementController::loop() {
    unsigned long now = millis();

    switch (_state) {

        case DRIVING:
            if (_switches.collision()) {
                enterState(BACKING_UP);
            } else {
                _motors.forward();
            }
            break;

        case BACKING_UP:
            if (now - _stateStart >= BACKUP_MS) {
                enterState(TURNING);
            }
            break;

        case TURNING:
            if (now - _stateStart >= _turnDuration) {
                if (_switches.collision()) {
                    enterState(TURNING);
                } else {
                    enterState(DRIVING);
                }
            }
            break;
    }
}
