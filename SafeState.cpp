#include "SafeState.h"

#define LOCKED_STATE_ADDR  0  // EEPROM address to store lock state
#define CODE_ADDR          1  // EEPROM address to store the code

SafeState::SafeState() {
    _locked = EEPROM.read(LOCKED_STATE_ADDR); // Read locked state from EEPROM
}

void SafeState::lock() {
    setLock(true);
}

bool SafeState::unlock(String code) {
    if (code == readCode()) {
        setLock(false);
        return true;
    }
    return false;
}

bool SafeState::locked() {
    return _locked;
}

bool SafeState::hasCode() {
    return readCode().length() > 0;
}

void SafeState::setCode(String newCode) {
    writeCode(newCode);
}

void SafeState::setLock(bool locked) {
    _locked = locked;
    EEPROM.write(LOCKED_STATE_ADDR, _locked); // Save lock state to EEPROM
}

String SafeState::readCode() {
    String code = "";
    for (int i = 0; i < 4; i++) {
        char c = EEPROM.read(CODE_ADDR + i);
        if (c == 0xFF) break; // Stop reading if EEPROM is uninitialized
        code += c;
    }
    return code;
}

void SafeState::writeCode(String newCode) {
    for (int i = 0; i < 4; i++) {
        EEPROM.write(CODE_ADDR + i, (i < newCode.length()) ? newCode[i] : 0);
    }
}