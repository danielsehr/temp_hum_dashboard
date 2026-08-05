#pragma once

#include "config/Config.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "storage/StorageManager.h"

#include <ESPAsyncWebServer.h>


class WebServer
{
public:
    explicit WebServer(WebSocketManager& webSocket, StorageManager& storageManager);

    void begin();

private:
    AsyncWebServer server_{Config::HTTP_PORT};

    WebSocketManager& webSocketManager_;

    StorageManager& storageManager_;

    void registerRoutes();
};
