#include <Pixel.h>

namespace FastLEDitor
{
    Pixel::Pixel(uint8_t x, uint8_t y)
    {
        this->x = x;
        this->y = y;
    }

    const Color &Pixel::getColor() const
    {
        return this->color;
    }

    uint8_t Pixel::getX() const
    {
        return this->x;
    }

    uint8_t Pixel::getY() const
    {
        return this->y;
    }

    void Pixel::setColor(const Color &color)
    {
        this->color = color;
    }

    void Pixel::setX(uint8_t x)
    {
        this->x = x;
    }

    void Pixel::setY(uint8_t y)
    {
        this->y = y;
    }

}