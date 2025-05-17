#include <Animation.h>

namespace FastLEDitor
{
    Animation::Animation()
    {
        ;
    }

    void Animation::addFrame(const Frame &frame)
    {
        this->frames.push_back(frame);
    }

    const Frame& Animation::getFrame(int index) const
    {
        return frames[index];
    }

    void Animation::setName(const String &name)
    {
        this->name = name;
    }

    const String &Animation::getName() const
    {
        return name;
    }

    String Animation::getNameNormalized() const
    {
        String name = this->getName();
        name.trim();
        name.toLowerCase();
        name.replace(' ', '-');

        return name;
    }

    uint8_t Animation::getNumFrames() const
    {
        return this->frames.size();
    }

    void Animation::nextFrame()
    {
        this->currentFrameIndex = (this->currentFrameIndex + 1) % this->frames.size();
    }
    int Animation::getCurrentFrameIndex() const
    {
        return currentFrameIndex;
    }

    void Animation::setCurrentFrameIndex(int index)
    {
        if (index >= 0 && index < frames.size())
        {
            currentFrameIndex = index;
        }
    }

    const std::vector<Frame> &Animation::getFrames() const
    {
        return frames;
    }
}
