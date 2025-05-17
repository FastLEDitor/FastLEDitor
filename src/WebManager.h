#include <ArduinoJson.h>
#include <WebServer.h>
#include <AnimationManager.h>
#include <vector>

#ifndef AP_SSID
#define AP_SSID "FastLEDitor"
#endif

#ifndef AP_PASSWORD
#define AP_PASSWORD "12345678"
#endif

namespace FastLEDitor
{
    class WebManager
    {
    public:
        WebManager(AnimationManager *p_delPanelManager);
        void tick();

    private:
        WebServer *m_webServer;
        AnimationManager *m_delPanelManager;
        void handleRoot();
        void getAnimations();
        void deleteAnimation(uint8_t id);
        void selectAnimation(uint8_t id);
        void getActiveAnimationIndex();
    };
}