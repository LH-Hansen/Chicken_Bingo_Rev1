#include "GameController.h"

GameController::GameController(MovementController& movement, ServoDriver& servo)
    : _movement(movement), _servo(servo)
{}

void GameController::updateSettings(uint16_t tMinMs, uint16_t tMaxMs,
                                    uint16_t gMinSec, uint16_t gMaxSec)
{
    _turnMinMs = tMinMs;
    _turnMaxMs = tMaxMs;
    _gameMinSec = gMinSec;
    _gameMaxSec = gMaxSec;
}

void GameController::startGame() {
    _servo.close();
    _gameDuration = random(_gameMinSec, _gameMaxSec) * 1000UL;
    _startTime = millis();
    _running = true;

    _movement.setTurnRange(_turnMinMs, _turnMaxMs);
}

void GameController::stopGame() {
    _running = false;
    _movement.enterStop();
    _servo.open();
}

uint32_t GameController::timeLeft() const {
    if (!_running) return 0;
    uint32_t elapsed = millis() - _startTime;
    if (elapsed >= _gameDuration) return 0;
    return (_gameDuration - elapsed) / 1000UL;
}

void GameController::loop() {
    if (!_running) {
        _movement.enterStop();
        return;
    }

    uint32_t elapsed = millis() - _startTime;
    if (elapsed >= _gameDuration) {
        stopGame();
        return;
    }

    _movement.loop();
}
