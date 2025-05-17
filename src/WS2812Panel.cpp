#include <WS2812Panel.h>
#include <vector>
#include <map>
#include <Pixel.h>

namespace FastLEDitor
{
    WS2812Panel::WS2812Panel()
    {
        ledsPanel = new CRGB[LED_COUNT_PANEL];
        FastLED.addLeds<WS2812, LED_PIN_PANEL, GRB>(ledsPanel, LED_COUNT_PANEL);
        FastLED.clear();
        FastLED.setBrightness(100);
    }

    void WS2812Panel::show()
    {
        FastLED.show();
    }

    int WS2812Panel::XY(int x, int y)
    {
        x = MATRIX_WIDTH_PANEL - 1 - x;
        if (y % 2 == 0)
        {
            return y * MATRIX_WIDTH_PANEL + x;
        }
        else
        {
            return y * MATRIX_WIDTH_PANEL + (MATRIX_WIDTH_PANEL - 1 - x);
        }
    }

    void WS2812Panel::drawFrame(Frame frame)
    {
        for (const Pixel &pixel : frame.getPixels())
        {
            int x = pixel.getX();
            int y = pixel.getY();
            CRGB color(pixel.getColor().getR(), pixel.getColor().getG(), pixel.getColor().getB());
            int index = XY(x, y);
            if (index >= 0 && index < LED_COUNT_PANEL)
                ledsPanel[index] = color;
        }
    }

    void WS2812Panel::eraseScreen()
    {
        FastLED.clear();
    }
}