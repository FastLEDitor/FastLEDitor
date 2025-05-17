#include <WebSerialCommandInterpreter.h>
#include <AnimationSerializer.h>

namespace FastLEDitor
{
    WebSerialCommandInterpreter::WebSerialCommandInterpreter(AnimationManager *p_delPanelManager)
    {
        this->m_delPanelManager = p_delPanelManager;
    }

    bool WebSerialCommandInterpreter::interpret(const uint8_t *commandBytes)
    {
        bool error = false;
        uint16_t offset = 0;
        uint8_t commandStringLength = commandBytes[offset++];
        if (commandStringLength > 64)
        {
            return false;
        }
        char commandBuffer[commandStringLength + 1]; //+1 pour le null termination byte

        for (int i = 0; i < commandStringLength; i++)
        {
            commandBuffer[i] = commandBytes[offset++];
        }
        commandBuffer[commandStringLength] = '\0';
        String command = String(commandBuffer);

        if (command == "addAnimation")
        {
            Animation animation = AnimationSerializer::deserialize(commandBytes, offset);
            for (const Animation &existingAnim : m_delPanelManager->getAnimations())
            {
                if (animation.getName() == existingAnim.getName())
                {
                    m_delPanelManager->deleteAnimationByName(existingAnim.getName());
                    break;
                }
            }
            m_delPanelManager->addAnimationToVector(animation);
            m_delPanelManager->saveAnimation(animation);
            delete[] commandBytes;
            return true;
        }
        else if (command == "getAnimation")
        {
        }
        else if (command == "getAnimationsNames")
        {
            size_t length = 2; // Two bytes for total length
            const std::vector<Animation> &animations = m_delPanelManager->getAnimations();
            length += animations.size(); // 1 byte for each length

            for (const Animation &animation : animations)
            {
                length += animation.getName().length();
            }

            uint8_t *data = new uint8_t[length];
            size_t animOffset = 0;
            for (const Animation &animation : animations)
            {
                const String &name = animation.getName();
                size_t len = name.length();
                data[animOffset++] = static_cast<uint8_t>(len);
                memcpy(data + animOffset, name.c_str(), len);
                animOffset += len;
            }

            const uint8_t START_MARKER = 0x7E;
            const uint8_t END_MARKER = 0x7F;

            size_t totalLength = 1 + 2 + length + 1;
            uint8_t *finalMessage = new uint8_t[totalLength];

            size_t pos = 0;
            finalMessage[pos++] = START_MARKER;
            finalMessage[pos++] = (length >> 8) & 0xFF;
            finalMessage[pos++] = length & 0xFF;
            memcpy(finalMessage + pos, data, length);
            pos += length;
            finalMessage[pos++] = END_MARKER;

            for (size_t i = 0; i < totalLength; i += CHUNK_SIZE)
            {
                size_t chunkSize = min(CHUNK_SIZE, totalLength - i);
                Serial.write(finalMessage + i, chunkSize);
                delay(10);
            }

            delete[] data;
            delete[] finalMessage;
        }

        return false;
    }

    void WebSerialCommandInterpreter::sendMessage(const String &message)
    {
        Serial.println("<<START>>");
        Serial.println(message);
        Serial.println("<<END>>");
    }
}