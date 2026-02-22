#include "DrumController.h"
#include "pins.h"
#include "Midi/MidiController.h"

DrumController::DrumController() = default;

void DrumController::begin()
{
    for (auto& pad : pads)
    {
        pad.begin();
    }
    MidiController::begin();
    modeSwitch.begin();
    modeLed.begin();
    modeLed.on();
}

void DrumController::update()
{
    updateMode();

    updatePads();
}

void DrumController::updateMode()
{
    modeSwitch.update();
    modeLed.update();

    if (modeSwitch.getState() != Config::IsCloneHeroMode)
    {
        modeLed.toggle();
        Config::IsCloneHeroMode = modeSwitch.getState();
        Serial.println("Clone Hero Mode: " + String(Config::IsCloneHeroMode ? "ON" : "OFF"));
    }
}

void DrumController::updatePads()
{
    for (auto& pad : pads)
    {
        pad.update();

        if (pad.isHit())
        {
            Serial.println("Pad hit: " + String(pad.getNote()) + " with velocity " + String(pad.getVelocity()));
            MidiController::noteOn(pad.getNote(), pad.getVelocity());
            MidiController::noteOff(pad.getNote());
        }
    }
}
