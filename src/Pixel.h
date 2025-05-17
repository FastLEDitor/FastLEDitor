#pragma once
#include <Arduino.h>
#include <Color.h>

namespace FastLEDitor
{
    class Pixel
    {
    private:
        uint8_t x;
        uint8_t y;
        Color color;

    public:
        Pixel(uint8_t x, uint8_t y);
        void setColor(const Color &color);
        void setX(uint8_t x);
        void setY(uint8_t y);
        const Color &getColor() const;
        uint8_t getX() const;
        uint8_t getY() const;
    };
}