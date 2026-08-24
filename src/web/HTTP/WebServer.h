#pragma once

#include "config/Config.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "storage/StorageManager.h"
#include "services/ExperimentService/ExperimentService.h"

#include <ESPAsyncWebServer.h>


class WebServer
{
public:
    explicit WebServer(
        WebSocketManager& webSocket, 
        StorageManager& storageManager, 
        ExperimentService& experimentService
    );

    void begin();

private:
    AsyncWebServer server_{Config::HTTP_PORT};

    WebSocketManager& webSocketManager_;

    StorageManager& storageManager_;

    ExperimentService& experimentService_;

    void registerRoutes();

    void handleStartExperiment(AsyncWebServerRequest* request);
    void handleStopExperiment(AsyncWebServerRequest* request);
    void handleExperimentStatus(AsyncWebServerRequest* request);

    void handleDownloadCsv(AsyncWebServerRequest* request);
};
