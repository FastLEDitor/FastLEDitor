#include <AnimationSerializer.h>

namespace FastLEDitor
{
    Animation AnimationSerializer::deserialize(const uint8_t *animationBytes, uint16_t offset)
    {
        uint8_t titleLength = animationBytes[offset++];

        char buffer[titleLength + 1];
        for (int i = 0; i < titleLength; i++)
        {
            buffer[i] = animationBytes[offset++];
        }
        buffer[titleLength] = '\0';
        String title = String(buffer);

        uint8_t numFrames = animationBytes[offset++];

        Animation animation;
        animation.setName(title);

        for (int i = 0; i < numFrames; i++)
        {
            uint8_t highByte = animationBytes[offset++];
            uint8_t lowByte = animationBytes[offset++];
            uint16_t numPixels = (highByte << 8) | lowByte;
            Frame frame;
            for (int j = 0; j < numPixels; j++)
            {
                uint8_t coords = animationBytes[offset++];
                uint8_t x = (coords & 0xf0) >> 4;
                uint8_t y = (coords & 0x0f);
                Pixel pixel(x, y);
                Color color(animationBytes[offset++], animationBytes[offset++], animationBytes[offset++]);
                pixel.setColor(color);
                frame.addPixel(pixel);
            }
            animation.addFrame(frame);
        }
        return animation;
    }

    const uint8_t *AnimationSerializer::serialize(const Animation &animation, size_t &outLength)
    {
        size_t titleLen = animation.getName().length();
        size_t totalSize = 0;

        totalSize += 1;        // 1 byte for title length
        totalSize += titleLen; // Title length
        totalSize += 1;        // Number of frames;

        for (const Frame &frame : animation.getFrames())
        {
            totalSize += 2;                              // Number of pixels;
            totalSize += frame.getNumPixels() * (1 + 3); // 1 byte for x/y, 3 bytes for colors
        }

        uint8_t *buffer = new uint8_t[totalSize];

        size_t offset = 0;

        buffer[offset++] = titleLen;
        memcpy(buffer + offset, animation.getName().c_str(), titleLen);
        offset += titleLen;

        buffer[offset++] = animation.getNumFrames();

        for (const Frame &frame : animation.getFrames())
        {
            uint16_t numPixels = frame.getNumPixels();
            buffer[offset++] = (numPixels >> 8) & 0xFF;
            buffer[offset++] = numPixels & 0xFF;

            for (const Pixel &pixel : frame.getPixels())
            {
                uint8_t coords = (pixel.getX() << 4) | (pixel.getY() & 0x0F);
                buffer[offset++] = coords;

                Color color = pixel.getColor();
                buffer[offset++] = color.getR();
                buffer[offset++] = color.getG();
                buffer[offset++] = color.getB();
            }
        }

        outLength = totalSize;
        return buffer;
    }
}
