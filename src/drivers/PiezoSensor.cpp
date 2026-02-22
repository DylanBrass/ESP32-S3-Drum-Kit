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
    const unsigned long nowMicros = micros();
    const unsigned long nowMillis = millis();
    // Dummy read to stabilize ADC for more accurate readings in the next call
    // This was something I saw online that could help
    analogRead(_pin);
    const int value = analogRead(_pin);
    _hit = false;

    switch (_state)
    {
    case PiezoState::Idle:
        {
            if (value > Config::Piezo::getCurrentThreshold())
            {
                // In Clone Hero mode, we skip the velocity calculation and use a fixed velocity for simplicity and consistency
                if (Config::IsCloneHeroMode)
                {
                    _velocity = Config::Piezo::CloneHeroDefaultVelocity;
                    _hit = true;
                    _lastHitTime = nowMillis;
                    _state = PiezoState::Cooldown;
                    _debugLed.on();
                    break;
                }

                _peakValue = value;
                _scanStartTime = nowMicros;
                _state = PiezoState::CapturingPeak;
            }
            break;
        }
    case PiezoState::CapturingPeak:
        {
            if (value > _peakValue)
                _peakValue = value;

            if (nowMicros - _scanStartTime >= Config::Piezo::ScanTime)
            {
                _velocity = calculateVelocity(_peakValue);

                _hit = true;
                _lastHitTime = nowMillis;

                _state = PiezoState::Cooldown;
                _debugLed.on();
            }
            break;
        }
    case PiezoState::Cooldown:
        {
            const bool timeExpired =
                nowMillis - _lastHitTime >= Config::Piezo::WaitTime;

            const bool signalReset =
                value < Config::Piezo::ResetThreshold;

            if (timeExpired && signalReset)
            {
                _state = PiezoState::Idle;
                _debugLed.off();
            }
            break;
        }
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
    const uint16_t threshold = Config::Piezo::getCurrentThreshold();

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
    auto velocity = static_cast<uint16_t>(normalized * Config::Midi::MaxMidiValue * 1.5f);

    velocity = constrain(velocity, Config::Midi::MinMidiValue, Config::Midi::MaxMidiValue);

    return velocity;
}
