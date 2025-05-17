#include <Arduino.h>
#include <FastLEDitor.h>
#include <LittleFS.h>

FastLEDitor::FastLEDitor* fastLEDitor = nullptr;

void setup() {
  if (!LittleFS.begin())
  {
    LittleFS.format();
    Serial.println("Failed to mount littlefs");
  }
  fastLEDitor = new FastLEDitor::FastLEDitor();
}

void loop() {
  fastLEDitor->tick();
}