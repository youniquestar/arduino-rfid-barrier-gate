#include "FeedbackManager.h"

FeedbackManager::FeedbackManager(uint8_t redPin, uint8_t greenPin, uint8_t buzzerPin)
    : _redPin(redPin), _greenPin(greenPin), _buzzerPin(buzzerPin) {}

void FeedbackManager::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_buzzerPin, OUTPUT);
    setIdle();
}

void FeedbackManager::setIdle() {
    digitalWrite(_redPin, HIGH);   // Solid Red = Barrier down / Standby
    digitalWrite(_greenPin, LOW);
    digitalWrite(_buzzerPin, LOW);
}

void FeedbackManager::signalSuccess() {
    digitalWrite(_redPin, LOW);
    digitalWrite(_greenPin, HIGH); // Solid Green = Passage permitted
    
    // Single pleasant confirmation chime
    digitalWrite(_buzzerPin, HIGH);
    delay(150);
    digitalWrite(_buzzerPin, LOW);
}

void FeedbackManager::signalDenied() {
    digitalWrite(_greenPin, LOW);
    
    // 3 rapid warning flashes & alert beeps
    for (uint8_t i = 0; i < 3; i++) {
        digitalWrite(_redPin, HIGH);
        digitalWrite(_buzzerPin, HIGH);
        delay(100);
        digitalWrite(_redPin, LOW);
        digitalWrite(_buzzerPin, LOW);
        delay(100);
    }
    
    digitalWrite(_redPin, HIGH); // Return to idle red
}
