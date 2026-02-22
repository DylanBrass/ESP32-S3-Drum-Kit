#pragma once
#include <cstdint>

namespace Config
{
    extern bool IsCloneHeroMode;
    namespace Switches
    {
        constexpr uint16_t DebounceDelay = 20; // ms
    }
    namespace Timing
    {
        constexpr uint32_t BlinkInterval = 1000;
    }

    namespace Midi
    {
        constexpr uint8_t OrangeNote = 36;
        constexpr uint8_t BlueNote = 38;
        constexpr uint8_t YellowNote = 37;
        constexpr uint8_t RedNote = 41;
        constexpr uint8_t GreenNote = 43;
        constexpr uint8_t HighGreenNote = 51;
        constexpr uint8_t HighBlueNote = 49;
        constexpr uint8_t HighYellowNote = 46;
        constexpr uint8_t DrumChannel = 10;
        constexpr uint8_t MaxMidiValue = 127;
        constexpr uint8_t MinMidiValue = 30;
        constexpr uint16_t PiezoThreshold = 250;
    }
    namespace CloneHero
    {
        constexpr uint16_t PiezoThreshold = 300;
    }

    namespace Piezo
    {
        extern uint16_t getCurrentThreshold();
        constexpr uint16_t ResetThreshold = 50;
        constexpr uint16_t WaitTime = 75;
        constexpr uint16_t ScanTime = 3000; // us
        constexpr uint16_t MaxADCValue = 4095;
        constexpr uint16_t CloneHeroDefaultVelocity = 110;
    }
}
