#pragma once
#include <Arduino.h>

class Led
{
public:
    explicit Led(uint8_t pin, bool activeHigh = true);

    void begin();

    void on();
    void off();
    void toggle();

    void blink(unsigned long interval);
    void stopBlink();                

    void update();

private:
    uint8_t _pin;
    bool _activeHigh;

    bool _state = false;

    bool _blinking = false;
    unsigned long _blinkInterval = 0;
    unsigned long _lastToggleTime = 0;

    void applyState();
};
