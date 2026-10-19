#pragma once
#include <Arduino.h>

class FeedbackManager {
public:
    FeedbackManager(uint8_t redPin, uint8_t greenPin, uint8_t buzzerPin);
    void begin();
    void setIdle();
    void signalSuccess();
    void signalDenied();

private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _buzzerPin;
};
