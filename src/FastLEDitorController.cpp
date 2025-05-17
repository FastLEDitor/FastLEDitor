#include <FastLEDitorController.h>

namespace FastLEDitor
{
    FastLEDitorController::FastLEDitorController()
    {

    }

    void FastLEDitorController::tick()
    {     
        if (!this->isInit())
        {
            return;
        }
        this->m_animationManager->tick();
        this->m_webSerialManager->tick();
        if (this->usingWebServer)
        {
            m_webManager->tick();
        }
    }

    void FastLEDitorController::init()
    {
        this->m_animationManager = new AnimationManager();
        this->m_webSerialManager = new WebSerialManager(new WebSerialCommandInterpreter(m_animationManager));
        if (this->usingWebServer)
        {
            this->m_webManager = new WebManager(m_animationManager);
        }
        this->isInitiatied = true;
    }

    bool FastLEDitorController::isInit()
    {
        return this-> isInitiatied;
    }

    void FastLEDitorController::useWebServer()
    {
        this->usingWebServer = true;
    }
}
