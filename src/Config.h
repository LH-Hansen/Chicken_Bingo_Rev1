#pragma once

#include <Arduino.h>  

// Motor pins
constexpr uint8_t PIN_IN1 = D2;
constexpr uint8_t PIN_IN2 = D1;
constexpr uint8_t PIN_IN3 = D5;
constexpr uint8_t PIN_IN4 = D6;

// Speed controlller
static const uint8_t PIN_MOTOR_EN = D8;

// Servo
static const uint8_t PIN_SERVO = D7; 

constexpr uint8_t HATCH_OPEN = 180;
constexpr uint8_t HATCH_CLOSED = 0;

// Switch
constexpr uint8_t PIN_SWITCH = D3;

// Tunable movement values
static const uint16_t BACKUP_MS   = 200;
static const uint16_t MIN_TURN_MS = 200;
static const uint16_t MAX_TURN_MS = 600;




