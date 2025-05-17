#pragma once
#include <FastLED.h>
#include <Frame.h>

#ifndef LED_PIN_PANEL
#define LED_PIN_PANEL 17
#endif

#define LED_COUNT_PANEL 256 // for 16x16 matrix example
#define MATRIX_WIDTH_PANEL 16
#define MATRIX_HEIGHT_PANEL 16

namespace FastLEDitor
{
    class WS2812Panel
    {
    private:
        CRGB *ledsPanel;

        unsigned long previousMillis = 0;

    public:
        WS2812Panel();
        void show();
        int XY(int x, int y);
        void drawFrame(Frame frame);
        void eraseScreen();
        void tick();
    };
}