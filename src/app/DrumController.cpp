#include "DrumController.h"
#include "pins.h"
#include "Midi/MidiController.h"

DrumController::DrumController() : _statusPin(Pins::StatusLed, false) {}

void DrumController::begin()
{
    _statusPin.begin();
    for (auto & pad : pads)
    {
        pad.begin();
    }

    MidiController::begin();
}

void DrumController::update()
{
    _statusPin.update();

    for (auto & pad : pads)
    {
        pad.update();

        if (pad.isHit())
        {
            Serial.println("Pad hit: " + String(pad.getNote()) + " with velocity: " + String(pad.getVelocity()));
            MidiController::noteOn(pad.getNote(), pad.getVelocity());
            MidiController::noteOff(pad.getNote());
            _statusPin.toggle();
        }
    }
}