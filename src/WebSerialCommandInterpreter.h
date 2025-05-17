#pragma once

#include <Arduino.h>
#include <AnimationManager.h>

namespace FastLEDitor
{
    class WebSerialCommandInterpreter
    {
    private:
        AnimationManager *m_delPanelManager = nullptr;
        const size_t CHUNK_SIZE = 256;

    public:
        WebSerialCommandInterpreter(AnimationManager *p_delPanelManager);
        bool interpret(const uint8_t *commandBytes);
        void sendMessage(const String &message);
    };
}
