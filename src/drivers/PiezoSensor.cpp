#include "PiezoSensor.h"
#include "config.h"

PiezoSensor::PiezoSensor(const uint8_t pin, const uint8_t note)
    : _pin(pin), _note(note), _velocity(0)
{
}

void PiezoSensor::begin() const
{
    pinMode(_pin, INPUT);
}

uint8_t PiezoSensor::getNote() const
{
    return _note;
}

uint16_t PiezoSensor::getVelocity() const
{
    return _velocity;
}

void PiezoSensor::update()
{
    const int value = analogRead(_pin);
    const unsigned long now = millis();
    _hit = false;

    if (_coolingDown)
    {
        const bool timeExpired = now - _lastHitTime >= Config::Piezo::WaitTime;
        const bool signalReset = value < _lastHitValue - Config::Piezo::ResetThreshold;

        if (timeExpired && signalReset)
        {
            _coolingDown = false;
        }
        else
        {
            return;
        }
    }

    if (value > Config::Piezo::Threshold)
    {
        Serial.println("Hit detected, scanning for peak...");
        int peak = value - Config::Piezo::Threshold;
        const unsigned long scanTimeStart = millis();

        while (millis() - scanTimeStart < Config::Piezo::ScanTime)
        {
            const int currentValue = analogRead(_pin);
            if (currentValue > peak)
            {
                peak = currentValue;
            }
        }

        Serial.println("Max value during scan: " + String(peak));

        _velocity = calculateVelocity(peak);

        _hit = true;
        _lastHitValue = value;
        _lastHitTime = now;
        _coolingDown = true;
    }
}

bool PiezoSensor::isHit() const
{
    return _hit;
}

uint16_t PiezoSensor::calculateVelocity(const int peak)
{
    constexpr uint16_t maxAdc = Config::Piezo::MaxADCValue;
    constexpr uint16_t threshold = Config::Piezo::Threshold;

    if (peak <= threshold)
        return 1;

    const float normalized = static_cast<float>(peak - threshold) /
                       static_cast<float>(maxAdc - threshold);

    auto velocity = static_cast<uint8_t>(normalized * 127.0f);

    velocity = constrain(velocity, 1, 127);

    return velocity;
}