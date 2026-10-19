/*
 * =========================================================================
 *   RFID-Controlled Wooden Barrier Gate Access System
 *   Target Microcontroller: Arduino Nano (ATmega328P) / Arduino Uno
 *   Actuator: TowerPro MG90S Metal-Gear Micro Servo
 *   RFID Transceiver: MFRC522 (13.56 MHz SPI Module)
 *
 *   REQUIRED ARDUINO LIBRARIES:
 *     1. "MFRC522" by GithubCommunity / Miguel Balboa
 *     2. "Servo" by Arduino
 * =========================================================================
 */

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#include "Config.h"
#include "GateController.h"
#include "FeedbackManager.h"
#include "AccessManager.h"

// Instantiate Hardware Modules
MFRC522 rfid(PIN_RC522_SS, PIN_RC522_RST);
GateController gate(PIN_SERVO, GATE_ANGLE_CLOSED, GATE_ANGLE_OPEN, STEP_DELAY_MS);
FeedbackManager feedback(PIN_LED_RED, PIN_LED_GREEN, PIN_BUZZER);

void setup() {
    Serial.begin(9600);
    while (!Serial && millis() < 3000); // Wait for serial monitor or 3s timeout

    Serial.println(F("=================================================="));
    Serial.println(F("   RFID Access Control Barrier Gate System       "));
    Serial.println(F("=================================================="));

    // Initialize SPI bus & RC522 Reader
    SPI.begin();
    rfid.PCD_Init();
    delay(50);
    rfid.PCD_DumpVersionToSerial();

    // Initialize Feedback Indicators & Actuator
    feedback.begin();
    gate.begin();

    Serial.println(F("System Ready: Present RFID Tag to scanner..."));
}

void loop() {
    // 1. Check for presence of RFID card / fob
    if (!rfid.PICC_IsNewCardPresent()) {
        return;
    }

    // 2. Read serial UID from the card
    if (!rfid.PICC_ReadCardSerial()) {
        return;
    }

    // 3. Output UID to Serial Monitor for identification
    AccessManager::printUID(rfid.uid.uidByte, rfid.uid.size);

    // 4. Validate scanned UID against authorized database
    if (AccessManager::verifyUID(rfid.uid.uidByte, rfid.uid.size)) {
        Serial.println(F(">> ACCESS GRANTED: Opening Barrier Gate."));
        
        feedback.signalSuccess();
        gate.open();
        
        Serial.print(F(">> Gate holding open for "));
        Serial.print(GATE_HOLD_MS);
        Serial.println(F(" ms..."));
        delay(GATE_HOLD_MS);
        
        Serial.println(F(">> Closing Barrier Gate."));
        gate.close();
        feedback.setIdle();
        Serial.println(F(">> System returned to IDLE standby."));
    } else {
        Serial.println(F(">> ACCESS DENIED: Unauthorized Tag!"));
        feedback.signalDenied();
        feedback.setIdle();
    }

    // 5. Cleanly stop encryption & halt PICC to prevent duplicate reads
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    
    // Short cooldown delay before accepting next tag
    delay(500);
}
