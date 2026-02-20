#pragma once
#include <cstdint>

namespace Config
{
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
        constexpr uint8_t YellowNote = 40;
        constexpr uint8_t RedNote = 41;
        constexpr uint8_t GreenNote = 43;
        extern bool CloneheroMode;
    }

    namespace Piezo
    {
        constexpr uint16_t Threshold = 300;
        constexpr uint16_t ResetThreshold = 50;
        constexpr uint16_t WaitTime = 75;
        constexpr uint16_t ScanTime = 3000; // us
        constexpr uint16_t MaxADCValue = 4095;
        constexpr uint16_t CloneHeroDefaultVelocity = 110;
    }
}
