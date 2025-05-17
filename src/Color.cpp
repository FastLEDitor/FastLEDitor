#include <Color.h>

namespace FastLEDitor
{
    Color::Color()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void Color::setR(uint8_t r)
    {
        this->r = r;
    }

    void Color::setG(uint8_t g)
    {
        this->g = g;
    }

    void Color::setB(uint8_t b)
    {
        this->b = b;
    }

    uint8_t Color::getR() const
    {
        return this->r;
    }

    uint8_t Color::getG() const
    {
        return this->g;
    }

    uint8_t Color::getB() const
    {
        return this->b;
    }
}
