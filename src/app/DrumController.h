#pragma once
#include <Arduino.h>
#include "../drivers/Led.h"
#include "../drivers/PiezoSensor.h"
#include "pins.h"
#include "config.h"

class DrumController
{
public:
    DrumController();
    void begin();
    void update();

private:
    static constexpr int numberOfPads = 5;
    Led _statusPin;
    PiezoSensor pads[numberOfPads] = {
        PiezoSensor(Pins::PadOrange, Config::Midi::OrangeNote),
        PiezoSensor(Pins::PadBlue, Config::Midi::BlueNote),
        PiezoSensor(Pins::PadYellow, Config::Midi::YellowNote),
        PiezoSensor(Pins::PadRed, Config::Midi::RedNote),
        PiezoSensor(Pins::PadGreen, Config::Midi::GreenNote)};
};