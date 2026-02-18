#include "Led.h"

Led::Led(uint8_t pin, bool activeHigh)
    : _pin(pin), _activeHigh(activeHigh) {}

void Led::begin() {
    pinMode(_pin, OUTPUT);
    off();
}

void Led::on() {
    _blinking = false;
    _state = true;
    applyState();
}

void Led::off() {
    _blinking = false;
    _state = false;
    applyState();
}

void Led::toggle() {
    _state = !_state;
    applyState();
}

void Led::blink(unsigned long interval) {
    _blinking = true;
    _blinkInterval = interval;
    _lastToggleTime = millis();
}

void Led::stopBlink() {
    _blinking = false;
}

void Led::update() {
    if (!_blinking) return;

    unsigned long now = millis();

    if (now - _lastToggleTime >= _blinkInterval) {
        _lastToggleTime = now;
        toggle();
    }
}

void Led::applyState() {
    if (_activeHigh) {
        digitalWrite(_pin, _state ? HIGH : LOW);
    } else {
        digitalWrite(_pin, _state ? LOW : HIGH);
    }
}
