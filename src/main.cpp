#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "app/DrumController.h"

DrumController drumController;

void setup()
{
  Serial.begin(115200);

  TinyUSBDevice.setManufacturerDescriptor("DrumCo");
  TinyUSBDevice.setProductDescriptor("ESP32 Drum");

  delay(200);

  drumController.begin();

  Serial.println("Drum Controller Initialized");
}

void loop()
{
  drumController.update();
}
