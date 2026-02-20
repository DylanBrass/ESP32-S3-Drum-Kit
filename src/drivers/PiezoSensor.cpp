#include "PiezoSensor.h"
#include "config.h"
#include "Led.h"

PiezoSensor::PiezoSensor(const uint8_t pin, const uint8_t note, const uint8_t debugLed)
    : _pin(pin), _note(note), _debugLed(debugLed), _velocity(0)
{
}

void PiezoSensor::begin()
{
    pinMode(_pin, INPUT);
    _debugLed.begin();
    _debugLed.off();
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
    int value = analogRead(_pin);
    const unsigned long now = millis();
    _hit = false;

    if (_coolingDown)
    {
        const bool timeExpired = now - _lastHitTime >= Config::Piezo::WaitTime;
        const bool signalReset = value < Config::Piezo::ResetThreshold;

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
        const unsigned long scanTimeStart = micros();

        if (Config::Midi::CloneheroMode)
        {
            // In Clone Hero mode, we skip the scanning and just use a fixed velocity for any hit above the threshold
            // This is to have a more stable experience since velocity is not always accurately detected with piezo sensors, especially with fast hits
            Serial.println("Clone Hero mode enabled:");
            _velocity = Config::Piezo::CloneHeroDefaultVelocity;
        }
        else
        {
            while (micros() - scanTimeStart < Config::Piezo::ScanTime)
            {
                const int currentValue = analogRead(_pin);
                if (currentValue > value)
                {
                    value = currentValue;
                }
            }

            Serial.println("Max value during scan: " + String(value));

            _velocity = calculateVelocity(value);
        }
        _debugLed.on();

        _hit = true;
        _lastHitValue = value;
        _lastHitTime = now;
        _coolingDown = true;
    }

    // Turn LED off when ready to hit again
    if (!_coolingDown)
    {
        _debugLed.off();
    }

    _debugLed.update();
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
    {
        Serial.println(
            "Peak value " + String(peak) + " is below or equal to threshold " + String(threshold) +
            ". Returning minimum velocity.");
        return 1;
    }

    const float normalized = static_cast<float>(peak) /
        static_cast<float>(maxAdc);

    // 1.5 is an empirical multiplier to make the velocity more responsive, adjust as needed
    // We also ensure that the velocity does not exceed 127, which is the maximum MIDI velocity
    auto velocity = static_cast<uint16_t>(normalized * 127.0f * 1.5f);

    velocity = constrain(velocity, 1, 127);

    return velocity;
}
