#include "WebSocketManager.h"
#include "utils/logger/Logger.h"

void WebSocketManager::begin(AsyncWebServer& server)
{
    webSocket_.onEvent(
        [this](
            AsyncWebSocket* server,
            AsyncWebSocketClient* client,
            AwsEventType type,
            void* arg,
            uint8_t* data,
            size_t len
        )
        {
            onEvent(server, client, type, arg, data, len);
        }

    );

    server.addHandler(&webSocket_);

    LOG_INFO("Websocket initialized.");
}

void WebSocketManager::onEvent(
    AsyncWebSocket* server,
    AsyncWebSocketClient* client,
    AwsEventType type,
    void* arg,
    uint8_t* data,
    size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        {
            LOG_INFO("Client connected.");
        
            newClient_ = client;
            
            break;
        }

    case WS_EVT_DISCONNECT:
        {
            LOG_INFO("Client disconnected.");
        
            if (newClient_ == client)
                {
                    newClient_ = nullptr;
                }

            break;
        }
        

    case WS_EVT_DATA:
    {
        String message;

        for (size_t i = 0; i < len; i++)
        {
            message += static_cast<char>(data[i]);
        }

        LOG_INFO(message.c_str());

        client->text("Message received.");

        break;
    }

    default:
        break;
    }
}

void WebSocketManager::broadcast(const char *message)
{
    webSocket_.textAll(message);
}

void send(AsyncWebSocketClient& client, const char* message)
{
    client.text(message);
}
