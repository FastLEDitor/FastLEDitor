#define AP_PASSWORD "87654321"
#define LED_PIN_PANEL 17

#include <Arduino.h>
#include <FastLEDitorController.h>
#include <LittleFS.h>

FastLEDitor::FastLEDitorController* controller = nullptr;


void setup() {
  Serial.begin(115200);
  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount littlefs");
  }
  controller = new FastLEDitor::FastLEDitorController();
  controller->useWebServer();
  controller->init();
}

void loop() {
  controller->tick();
}