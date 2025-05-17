#include <AnimationManager.h>
#include <LittleFS.h>
#include <AnimationSerializer.h>

namespace FastLEDitor
{
    AnimationManager::AnimationManager()
    {
        this->m_panel = new WS2812Panel();
        previousMillis = millis();

        currentAnimationIndex = 0;
        this->loadAnimations();
    }

    const std::vector<Animation> &AnimationManager::getAnimations()
    {
        return this->animations;
    }

    void AnimationManager::setCurrentAnimationIndex(u_int8_t index)
    {
        if (index < 0 || index > this->animations.size() - 1)
        {
            return;
        }

        currentAnimationIndex = index;
        m_panel->eraseScreen();
    }

    Animation *AnimationManager::getAnimationById(int p_index)
    {
        if (p_index < animations.size() && p_index >= 0)
        {
            return &animations[p_index];
        }
        return nullptr;
    }

    const Animation *AnimationManager::getAnimationByName(const String &name)
    {
        const Animation *foundAnimation = nullptr;
        for (const Animation &animation : this->getAnimations())
        {
            if (animation.getName() == name)
            {
                foundAnimation = &animation;
                break;
            }
        }

        return foundAnimation;
    }

    bool AnimationManager::deleteAnimationByName(const String &name)
    {
        for (int i = 0; i < this->animations.size(); i++)
        {
            if (animations[i].getName() == name)
            {
                this->animations.erase(animations.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool AnimationManager::deleteAnimationById(int p_index)
    {
        if (p_index < animations.size() && p_index >= 0)
        {
            animations.erase(animations.begin() + p_index);
            if (p_index > 0)
            {
                currentAnimationIndex--;
            }
            return true;
        }
        return false;
    }

    void AnimationManager::changeAnimationState(AnimationState animationState)
    {
        this->animationState = animationState;
    }

    int AnimationManager::getCurrentAnimationIndex()
    {
        return this->currentAnimationIndex;
    }

    void AnimationManager::loadAnimations()
    {
        if (!LittleFS.begin())
        {
            Serial.println("File system is not mounted. Cannot load animations.");
            return;
        }
        File dir = LittleFS.open("/animations");

        if (!dir || !dir.isDirectory())
        {
            Serial.println("Animations directory doesn't exist.");
        }

        File file = dir.openNextFile();
        while (file)
        {
            String fileName = file.name();

            if (!file.isDirectory() && fileName.endsWith(".bin"))
            {
                size_t size = file.size();
                uint8_t *buffer = new uint8_t[size];

                file.read(buffer, size);
                Animation animation = AnimationSerializer::deserialize(buffer, 0);

                this->addAnimationToVector(animation);

                delete[] buffer;
            }
            file = dir.openNextFile();
        }
    }

    void AnimationManager::addAnimationToVector(const Animation &animation)
    {
        this->animations.push_back(animation);
    }

    void AnimationManager::saveAnimation(const Animation &animation)
    {
        if (!LittleFS.begin())
        {
            Serial.println("File system is not mounted. Cannot save animation.");
            return;
        }
        if (!LittleFS.exists("/animations"))
        {
            if (!LittleFS.mkdir("/animations"))
            {
                return;
            }
        }

        String path = String("/animations/") + animation.getNameNormalized() + String(".bin");
        File file = LittleFS.open(path, "w");

        if (!file)
        {
            return;
        }
        size_t animationSize = 0;
        const uint8_t *animationBytes = AnimationSerializer::serialize(animation, animationSize);

        file.write(animationBytes, animationSize);
        return;
    }

    void AnimationManager::tick()
    {
        if (this->animations.empty())
        {
            return;
        }

        unsigned long currentTime = millis();
        Animation &currentAnimation = this->animations[this->currentAnimationIndex];

        const std::vector<Frame> &animationFrames = currentAnimation.getFrames();

        if (animationFrames.empty())
        {
            return;
        }

        

        if (currentTime - lastFrameUpdateTime >= 200)
        {
            lastFrameUpdateTime = currentTime;
            int currentFrameIndex = currentAnimation.getCurrentFrameIndex();
            if (currentFrameIndex == 0)
            {
                this->m_panel->eraseScreen();
            }

            currentAnimation.nextFrame();

            const Frame &currentFrame = currentAnimation.getFrame(currentFrameIndex);

            if (currentFrameIndex == animationFrames.size() - 1)
            {
                if (this->animationState == AnimationState::Increment)
                {
                    this->setCurrentAnimationIndex((currentAnimationIndex + 1) % this->animations.size());
                    currentAnimation.setCurrentFrameIndex(0);
                }
            }
            this->m_panel->drawFrame(currentFrame);
            m_panel->show();
        }
    }
}
