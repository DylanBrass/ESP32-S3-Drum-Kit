#pragma once
#include <Arduino.h>

#include "Led.h"

class PiezoSensor
{
public:
    explicit PiezoSensor(uint8_t pin, uint8_t note, uint8_t debugLed);
    void begin();
    void update();
    uint8_t getNote() const;
    uint16_t getVelocity() const;
    bool isHit() const;
    static uint16_t calculateVelocity(int peak) ;

private:
    uint8_t _pin;
    uint8_t _note;
    Led _debugLed;
    bool _coolingDown = false;
    uint16_t _lastHitValue = 0;
    uint32_t _lastHitTime = 0;
    bool _hit = false;
    uint16_t _velocity;
};
