#include "Switch.h"
#include <Arduino.h>

#include "config.h"

Switch::Switch(const uint8_t pin) : _pin(pin)
{
}

void Switch::begin() const
{
    pinMode(_pin, INPUT_PULLUP);
}

bool Switch::getState() const
{
    return _currentState;
}

void Switch::update()
{
    const bool reading = digitalRead(_pin) == LOW;

    if (reading && !_lastPhysicalState
        && millis() - _lastPressedTime > Config::Switches::DebounceDelay)
    {
        _currentState = !_currentState;

        Serial.println("Switch is " + String(_currentState ? "on" : "off"));

        _lastPressedTime = millis();
    }
    _lastPhysicalState = reading;
}
