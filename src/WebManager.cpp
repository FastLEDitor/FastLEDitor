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
                                {  });

        m_webServer->serveStatic("/bootstrap/js/bootstrap.min.js", LittleFS, "/bootstrap/js/bootstrap.min.js");
        m_webServer->serveStatic("/bootstrap/css/bootstrap.min.css", LittleFS, "/bootstrap/css/bootstrap.min.css");
        m_webServer->serveStatic("/bootstrap/js/bootstrap.min.js.map", LittleFS, "/bootstrap/js/bootstrap.min.js.map");
        m_webServer->serveStatic("/bootstrap/css/bootstrap.min.css.map", LittleFS, "/bootstrap/css/bootstrap.min.css.map");

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
        File animationsPage = LittleFS.open("/animations.html");

        if (!animationsPage)
        {
            m_webServer->send(500, "text/plain", "Failed to open animations.html");
            return;
        }

        m_webServer->streamFile(animationsPage, "text/html");
        animationsPage.close();
    }

    void WebManager::tick()
    {
        m_webServer->handleClient();
    }
}