#include <Adafruit_TinyUSB.h>
#include "MidiController.h"
#include <Arduino.h>
#include <MIDI.h>

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MidiUsb);

void MidiController::begin()
{
    TinyUSBDevice.setManufacturerDescriptor("Chuck DrumCo");
    TinyUSBDevice.setProductDescriptor("ESP32 Drum");
    MidiUsb.begin(MIDI_CHANNEL_OMNI);
    Serial.println("Midi USB setup done");
}

void MidiController::noteOn(const uint8_t note,const uint8_t velocity, const uint8_t channel)
{
    MidiUsb.sendNoteOn(note, velocity, channel);
}

void MidiController::noteOff(const uint8_t note, const uint8_t channel)
{
    MidiUsb.sendNoteOff(note, 0, channel);
}
