#include <AnimationManager.h>
#include <WebSerialManager.h>
#if defined(ESP32)
#include <WebManager.h>
#endif

namespace FastLEDitor
{
    class FastLEDitor
    {
    public:
        FastLEDitor();
        void tick();
    private:
        AnimationManager *m_animationManager = nullptr;
        WebSerialManager* m_webSerialManager = nullptr;
#if defined(ESP32)
        WebManager *m_webManager = nullptr;
        bool usingWebServer = false;
#endif

    };
}