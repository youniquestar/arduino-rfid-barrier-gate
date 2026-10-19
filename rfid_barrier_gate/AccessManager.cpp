#include "AccessManager.h"

bool AccessManager::verifyUID(const byte* scannedUid, byte length) {
    if (length != UID_LENGTH) {
        return false;
    }

    // Constant-time check against authorized UID table
    for (size_t i = 0; i < AUTHORIZED_COUNT; i++) {
        bool match = true;
        for (size_t b = 0; b < UID_LENGTH; b++) {
            if (scannedUid[b] != AUTHORIZED_UIDS[i][b]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

void AccessManager::printUID(const byte* scannedUid, byte length) {
    Serial.print(F("Scanned UID: "));
    for (byte i = 0; i < length; i++) {
        if (scannedUid[i] < 0x10) Serial.print(F("0"));
        Serial.print(scannedUid[i], HEX);
        if (i < length - 1) Serial.print(F(":"));
    }
    Serial.println();
}
