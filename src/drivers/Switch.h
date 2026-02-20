#pragma once
#include <cstdint>

class Switch
{
public:
    explicit Switch(uint8_t pin);
    void begin() const;
    void update();
    bool getState() const;
private:
    uint8_t _pin;
    bool _currentState = false;
    bool _lastPhysicalState = false;
    unsigned long _lastPressedTime = 0;
};