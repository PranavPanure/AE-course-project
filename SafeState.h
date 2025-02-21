#ifndef SAFESTATE_H
#define SAFESTATE_H

#include <Arduino.h>
#include <EEPROM.h>

class SafeState {
  public:
    SafeState();
    void lock();
    bool unlock(String code);
    bool locked();
    bool hasCode();
    void setCode(String newCode);

  private:
    void setLock(bool locked);
    bool _locked;
    String readCode();
    void writeCode(String newCode);
};

#endif /* SAFESTATE_H */