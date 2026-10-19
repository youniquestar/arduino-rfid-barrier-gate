#include "GateController.h"

GateController::GateController(uint8_t servoPin, int closedAngle, int openAngle, uint8_t stepDelay)
    : _servoPin(servoPin), _closedAngle(closedAngle), _openAngle(openAngle),
      _stepDelay(stepDelay), _currentAngle(closedAngle) {}

void GateController::begin() {
    _servo.attach(_servoPin);
    _servo.write(_closedAngle);
    _currentAngle = _closedAngle;
    delay(500); // Allow physical arm to settle
}

void GateController::open() {
    // Stepped angular interpolation prevents gear shock and protects the wooden arm
    if (_currentAngle < _openAngle) {
        for (int pos = _currentAngle; pos <= _openAngle; pos++) {
            _servo.write(pos);
            delay(_stepDelay);
        }
    } else {
        for (int pos = _currentAngle; pos >= _openAngle; pos--) {
            _servo.write(pos);
            delay(_stepDelay);
        }
    }
    _currentAngle = _openAngle;
}

void GateController::close() {
    // Gentle stepped descent
    if (_currentAngle > _closedAngle) {
        for (int pos = _currentAngle; pos >= _closedAngle; pos--) {
            _servo.write(pos);
            delay(_stepDelay);
        }
    } else {
        for (int pos = _currentAngle; pos <= _closedAngle; pos++) {
            _servo.write(pos);
            delay(_stepDelay);
        }
    }
    _currentAngle = _closedAngle;
}

bool GateController::isClosed() const {
    return _currentAngle == _closedAngle;
}

int GateController::getCurrentAngle() const {
    return _currentAngle;
}
