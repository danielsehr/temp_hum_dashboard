#pragma once

#include "config/Config.h"
#include "web/WebSocketManager/WebSocketManager.h"

#include <ESPAsyncWebServer.h>


class WebServer
{
public:
    explicit WebServer(WebSocketManager& webSocket);

    void begin();

private:
    AsyncWebServer server_{Config::HTTP_PORT};

    WebSocketManager& webSocketManager_;

    void registerRoutes();
};
