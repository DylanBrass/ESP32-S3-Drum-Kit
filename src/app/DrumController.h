#pragma once
#include <Arduino.h>
#include "../drivers/Led.h"
#include "../drivers/PiezoSensor.h"
#include "pins.h"
#include "config.h"
#include "drivers/Switch.h"

class DrumController
{
public:
    DrumController();
    void begin();
    void update();

private:
    static constexpr int numberOfPads = 5;
    Switch modeSwitch{Pins::ModeSwitch};
    PiezoSensor pads[numberOfPads] = {
        PiezoSensor(Pins::PadOrange, Config::Midi::OrangeNote, Pins::OrangeDebugLed),
        PiezoSensor(Pins::PadBlue, Config::Midi::BlueNote, Pins::BlueDebugLed),
        PiezoSensor(Pins::PadYellow, Config::Midi::YellowNote, Pins::YellowDebugLed),
        PiezoSensor(Pins::PadRed, Config::Midi::RedNote, Pins::RedDebugLed),
        PiezoSensor(Pins::PadGreen, Config::Midi::GreenNote, Pins::GreenDebugLed)
    };
    void updateMode();
    void updatePads();
};
