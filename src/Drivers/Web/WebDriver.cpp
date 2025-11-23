#include "WebDriver.h"

WebDriver::WebDriver(GameController& game)
    : _game(game)
{}

void WebDriver::begin() {
    LittleFS.begin();

    WiFi.mode(WIFI_AP);
    WiFi.softAP("ChickenBingo", "12345678");

    _server.on("/",       HTTP_GET,  std::bind(&WebDriver::handleIndex, this));
    _server.on("/state",  HTTP_GET,  std::bind(&WebDriver::handleState, this));
    _server.on("/start",  HTTP_GET,  std::bind(&WebDriver::handleStart, this));
    _server.on("/stop",   HTTP_GET,  std::bind(&WebDriver::handleStop,  this));
    _server.on("/config", HTTP_POST, std::bind(&WebDriver::handleConfig, this));

    _server.begin();
}

void WebDriver::loop() {
    _server.handleClient();
}

void WebDriver::handleIndex() {
    if (!LittleFS.exists("/index.html")) {
        _server.send(404, "text/plain", "index.html missing");
        return;
    }
    File f = LittleFS.open("/index.html", "r");
    _server.streamFile(f, "text/html");
    f.close();
}

void WebDriver::handleState() {
    String json = "{";

    json += "\"running\":"     + String(_game.isRunning() ? "true" : "false") + ",";
    json += "\"timeLeft\":"    + String(_game.timeLeft()) + ",";
    json += "\"turnMin\":"     + String(_game.getTurnMin()) + ",";
    json += "\"turnMax\":"     + String(_game.getTurnMax()) + ",";
    json += "\"gameMin\":"     + String(_game.getGameMin()) + ",";
    json += "\"gameMax\":"     + String(_game.getGameMax());

    json += "}";

    _server.send(200, "application/json", json);
}

void WebDriver::handleStart() {
    _game.startGame();
    _server.send(200, "text/plain", "Game Started");
}

void WebDriver::handleStop() {
    _game.stopGame();
    _server.send(200, "text/plain", "Game Stopped");
}

void WebDriver::handleConfig() {
    if (!_server.hasArg("tMin") || !_server.hasArg("tMax") ||
        !_server.hasArg("gMin") || !_server.hasArg("gMax"))
    {
        _server.send(400, "text/plain", "Missing parameters");
        return;
    }

    uint16_t tMin = _server.arg("tMin").toInt();
    uint16_t tMax = _server.arg("tMax").toInt();
    uint16_t gMin = _server.arg("gMin").toInt();
    uint16_t gMax = _server.arg("gMax").toInt();

    _game.updateSettings(tMin, tMax, gMin, gMax);

    _server.send(200, "text/plain", "Settings Updated");
}
