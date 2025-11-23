#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "Controllers/GameController.h"

class WebDriver {
public:
    WebDriver(GameController& game);

    void begin();
    void loop();

private:
    ESP8266WebServer _server{80};
    GameController& _game;

    void handleIndex();
    void handleState();
    void handleStart();
    void handleStop();
    void handleConfig();
};
