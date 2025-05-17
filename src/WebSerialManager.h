#pragma once
#include <WebSerialCommandInterpreter.h>

namespace FastLEDitor
{
    class WebSerialManager
    {
    private:
        WebSerialCommandInterpreter *m_commandInterpreter;

    public:
        WebSerialManager(WebSerialCommandInterpreter *p_commandInterpreter);
        void tick();
    };
}