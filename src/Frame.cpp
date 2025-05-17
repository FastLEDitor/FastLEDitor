#include <Frame.h>

namespace FastLEDitor
{
    Frame::Frame()
    {
    }
    void Frame::addPixel(const Pixel &pixel)
    {
        pixels.push_back(pixel);
    }

    const std::vector<Pixel> &Frame::getPixels() const
    {
        return pixels;
    }

    uint16_t Frame::getNumPixels() const
    {
        return this->pixels.size();
    }
}