#include <FastLEDitor.h>

namespace FastLEDitor
{
    FastLEDitor::FastLEDitor()
    {
        Serial.begin(115200);
        m_animationManager = new AnimationManager();
        m_webSerialManager = new WebSerialManager(new WebSerialCommandInterpreter(m_animationManager));
#if defined(ESP32)
        m_webManager = new WebManager(m_animationManager);
#endif
    }

    void FastLEDitor::tick()
    {
        m_animationManager->tick();
        m_webSerialManager->tick();
#if defined(ESP32)
        if (this->usingWebServer)
        {
            m_webManager->tick();
        }
#endif
    }
}