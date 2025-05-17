#pragma once
#include <Arduino.h>

namespace FastLEDitor
{
    class Color
    {
    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;

    public:
        Color();
        Color(uint8_t r, uint8_t g, uint8_t b);
        void setR(uint8_t r);
        void setG(uint8_t g);
        void setB(uint8_t b);
        uint8_t getR() const;
        uint8_t getG() const;
        uint8_t getB() const;
    };
}
