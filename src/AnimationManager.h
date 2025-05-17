#pragma once
#include <Arduino.h>
#include <FastLED.h>

#include <vector>
#include <Animation.h>
#include <Frame.h>
#include <Pixel.h>
#include <WS2812Panel.h>
#include <LittleFS.h>
#include <AnimationState.h>

namespace FastLEDitor
{
    class AnimationManager
    {
    private:
        WS2812Panel *m_panel;
        int countdownValue = 10;
        unsigned long previousMillis;
        unsigned long lastUpdateTime = 0;

        std::vector<Animation> animations; // Vector to hold animation functions
        int currentAnimationIndex = 0;     // Index of the current animation

        unsigned long lastFrameUpdateTime = 0; // Temps du dernier changement de frame
        AnimationState animationState = AnimationState::Increment;
    public:
        AnimationManager();

        const std::vector<Animation> &getAnimations();

        void showTime();
        void theFinalCountdown();

        void loadAnimations();
        void addAnimationToVector(const Animation &animation);
        void saveAnimation(const Animation &animation);
        Animation *getAnimationById(int p_index);
        const Animation *getAnimationByName(const String &name);
        bool deleteAnimationById(int p_index);
        bool deleteAnimationByName(const String &name);
        void changeAnimationState(AnimationState animationState);

        int getCurrentAnimationIndex();
        void setCurrentAnimationIndex(u_int8_t p_index);

        void tick();
    };
}
