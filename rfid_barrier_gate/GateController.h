#pragma once
#include <Arduino.h>
#include <Servo.h>

class GateController {
public:
    GateController(uint8_t servoPin, int closedAngle, int openAngle, uint8_t stepDelay);
    void begin();
    void open();
    void close();
    bool isClosed() const;
    int getCurrentAngle() const;

private:
    uint8_t _servoPin;
    int _closedAngle;
    int _openAngle;
    uint8_t _stepDelay;
    int _currentAngle;
    Servo _servo;
};
