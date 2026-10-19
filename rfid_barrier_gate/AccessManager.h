#pragma once
#include <Arduino.h>
#include "Config.h"

class AccessManager {
public:
    static bool verifyUID(const byte* scannedUid, byte length);
    static void printUID(const byte* scannedUid, byte length);
};
