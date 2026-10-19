#pragma once
#include <Arduino.h>

// =========================================================================
//  HARDWARE PIN DEFINITIONS (Arduino Nano V3.0 / Uno)
// =========================================================================

// MFRC522 RFID SPI Interface
// Note: Hardware SPI pins on ATmega328P: SCK=D13, MISO=D12, MOSI=D11
constexpr uint8_t PIN_RC522_RST = 9;   // RC522 Reset Pin
constexpr uint8_t PIN_RC522_SS  = 10;  // RC522 Slave Select / SDA Pin

// Actuator Pin
constexpr uint8_t PIN_SERVO     = 3;   // TowerPro MG90S Metal-Gear Micro Servo (PWM)

// Audio-Visual Feedback Indicators
constexpr uint8_t PIN_LED_RED   = 2;   // Standby / Access Denied LED (via 220Ω)
constexpr uint8_t PIN_LED_GREEN = 4;   // Access Granted LED (via 220Ω)
constexpr uint8_t PIN_BUZZER    = 5;   // Active 5V Piezo Buzzer

// =========================================================================
//  MECHANICAL & TIMING PARAMETERS
// =========================================================================
constexpr int GATE_ANGLE_CLOSED = 0;    // Gate horizontal / barrier down (degrees)
constexpr int GATE_ANGLE_OPEN   = 90;   // Gate vertical / barrier open (degrees)
constexpr uint16_t GATE_HOLD_MS = 4000; // Time gate remains open before auto-closing (ms)
constexpr uint8_t STEP_DELAY_MS = 15;   // Milliseconds per angular degree sweep (smooth interpolation)

// =========================================================================
//  ACCESS CONTROL WHITELIST (Mifare Classic 1K 4-byte UIDs)
// =========================================================================
constexpr size_t UID_LENGTH = 4;

// Replace these with your physical card / keyfob UIDs!
const uint8_t AUTHORIZED_UIDS[][UID_LENGTH] = {
    {0xDE, 0xAD, 0xBE, 0xEF}, // Primary Master / Admin Tag
    {0xA1, 0xB2, 0xC3, 0xD4}, // Secondary User Tag
    {0x73, 0x4B, 0x92, 0x1A}  // Authorized Vehicle Fob
};

constexpr size_t AUTHORIZED_COUNT = sizeof(AUTHORIZED_UIDS) / sizeof(AUTHORIZED_UIDS[0]);
