#pragma once

#include "config/Config.h"
#include "web/WebSocketManager/WebSocketManager.h"

#include <ESPAsyncWebServer.h>


class WebServer
{
public:

    void begin();


private:

    AsyncWebServer server{Config::HHTP_PORT};

    WebSocketManager webSocket;

    void registerRoutes();
};
