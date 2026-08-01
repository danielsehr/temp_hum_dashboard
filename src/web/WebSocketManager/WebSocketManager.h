#pragma once

#include <ESPAsyncWebServer.h>


class WebSocketManager
{
public:

    WebSocketManager();

    void begin(AsyncWebServer& server);

    void broadcast(const char* message);

private:

    AsyncWebSocket webSocket;

    static void onEvent(
        AsyncWebSocket* server,
        AsyncWebSocketClient* client,
        AwsEventType type,
        void* arg,
        uint8_t* data,
        size_t len
    );
};