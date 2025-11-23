#pragma once
#include <Arduino.h>
#include "MovementController.h"
#include "../Drivers/ServoDriver.h"

class GameController {
public:
    GameController(MovementController& movement, ServoDriver& servo);

    void begin() {}
    void loop();

    void startGame();
    void stopGame();

    void updateSettings(uint16_t tMinMs, uint16_t tMaxMs,
                        uint16_t gMinSec, uint16_t gMaxSec);

    bool isRunning() const { return _running; }
    uint32_t timeLeft() const;

    uint16_t getTurnMin() const { return _turnMinMs; }
    uint16_t getTurnMax() const { return _turnMaxMs; }
    uint16_t getGameMin() const { return _gameMinSec; }
    uint16_t getGameMax() const { return _gameMaxSec; }

private:
    MovementController& _movement;
    ServoDriver& _servo;

    bool _running = false;
    uint32_t _startTime = 0;
    uint32_t _gameDuration = 0;

    uint16_t _turnMinMs = 200;
    uint16_t _turnMaxMs = 600;
    uint16_t _gameMinSec = 30;
    uint16_t _gameMaxSec = 60;
};
