#include <Arduino.h>
#include "Drivers/MotorDriver.h"
#include "Drivers/SwitchDriver.h"
#include "Controllers/MovementController.h"
#include "Controllers/GameController.h"
#include "Drivers/Web/WebDriver.h"
#include "Drivers/ServoDriver.h"

MotorDriver motors;
SwitchDriver switches;
ServoDriver servo;
MovementController movement(motors, switches);
GameController game(movement, servo);
WebDriver web(game);

void setup() {
    randomSeed(analogRead(A0));

    servo.begin(PIN_SERVO);

    movement.begin();
    game.begin();
    web.begin();
}

void loop() {
    web.loop();
    game.loop();
}
