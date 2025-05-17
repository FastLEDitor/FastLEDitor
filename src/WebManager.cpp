#include <WebManager.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <uri/UriBraces.h>

namespace FastLEDitor
{
    WebManager::WebManager(AnimationManager *p_delPanelManager)
    {
        WiFi.softAP(AP_SSID, AP_PASSWORD);

        m_webServer = new WebServer(80);
        this->m_delPanelManager = p_delPanelManager;

        m_webServer->on("/", [this]()
                        { this->handleRoot(); });

        m_webServer->on("/api/animation", HTTP_GET, [this]()
                        { this->getAnimations(); });

        m_webServer->on("/api/animation/active", HTTP_GET, [this]()
                        { this->getActiveAnimationIndex(); });

        m_webServer->on(UriBraces("/api/animation/{}"), HTTP_DELETE, [this]()
                        { this->deleteAnimation(atoi(this->m_webServer->pathArg(0).c_str())); });

        m_webServer->on(UriBraces("/api/animation/{}"), HTTP_POST, [this]()
                        { this->selectAnimation(atoi(this->m_webServer->pathArg(0).c_str())); });

        m_webServer->on("/favicon.ico", HTTP_GET, [this]()
                        {
                            this->m_webServer->send(204); // No Content
                        });

        m_webServer->onNotFound([this]()
                                { Serial.println(this->m_webServer->uri()); });

        m_webServer->begin();
    }

    void WebManager::getActiveAnimationIndex()
    {
        this->m_webServer->send(200, "text/plain", String(this->m_delPanelManager->getCurrentAnimationIndex()));
    }

    void WebManager::getAnimations()
    {
        JsonDocument doc;
        JsonArray animationArray = doc.to<JsonArray>();

        std::vector<Animation> animations = m_delPanelManager->getAnimations();
        for (int i = 0; i < animations.size(); i++)
        {
            JsonObject animationObj = animationArray.add<JsonObject>();
            animationObj["id"] = i;
            animationObj["name"] = animations[i].getName();
        }

        String jsonResponse;
        serializeJson(doc, jsonResponse);

        m_webServer->send(200, "application/json", jsonResponse);
    }

    void WebManager::deleteAnimation(uint8_t id)
    {
        if (m_delPanelManager->deleteAnimationById(id))
        {
            m_webServer->send(204);
        }
        else
        {
            m_webServer->send(400, "application/json", "Cannot delete animation");
        }
    }

    void WebManager::selectAnimation(uint8_t id)
    {
        m_delPanelManager->setCurrentAnimationIndex(id);
        
            m_webServer->send(200, "application/json", "Animation selected succesfully");


    }

    void WebManager::handleRoot()
    {
    }

    void WebManager::tick()
    {
        m_webServer->handleClient();
    }
}