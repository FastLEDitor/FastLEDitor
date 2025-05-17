#include <AnimationManager.h>
#include <WebSerialManager.h>

#include <WebManager.h>

namespace FastLEDitor
{
    class FastLEDitorController
    {
    public:
        FastLEDitorController();
        void tick();
        void init();
        bool isInit();
        void useWebServer();
    private:
        AnimationManager *m_animationManager = nullptr;
        WebSerialManager *m_webSerialManager = nullptr;

        bool isInitiatied = false;

        WebManager *m_webManager = nullptr;
        bool usingWebServer = false;
    };
}