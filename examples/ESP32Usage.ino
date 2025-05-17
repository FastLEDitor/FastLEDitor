#include <Arduino.h>
#include <FastLEDitor.h>
#include <LittleFS.h>

FastLEDitor::Controller* fastLEDitor = nullptr;

void setup() {
  if (!LittleFS.begin())
  {
    LittleFS.format();
    Serial.println("Failed to mount littlefs");
  }
  fastLEDitor = new FastLEDitor::Controller();
  fastLEDitor->useWebServer();
  fastLEDitor->init();
}

void loop() {
  fastLEDitor->tick();
}