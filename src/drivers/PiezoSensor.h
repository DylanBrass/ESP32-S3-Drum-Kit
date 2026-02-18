#pragma once
#include <Arduino.h>

class PiezoSensor
{
public:
    explicit PiezoSensor(uint8_t pin, uint8_t note);
    void begin() const;
    void update();
    uint8_t getNote() const;
    uint16_t getVelocity() const;
    bool isHit() const;
    static uint16_t calculateVelocity(int peak) ;

private:
    uint8_t _pin;
    uint8_t _note;
    bool _coolingDown = false;
    uint16_t _lastHitValue = 0;
    uint32_t _lastHitTime = 0;
    bool _hit = false;
    uint16_t _velocity;
};
