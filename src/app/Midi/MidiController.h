#pragma once

class MidiController
{
public:
    static void begin();
    static void noteOn(uint8_t note, uint8_t velocity = 100, uint8_t channel = 10);
    static void noteOff(uint8_t note, uint8_t channel = 10);
};
