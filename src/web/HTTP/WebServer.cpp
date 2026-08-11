#include "WebServer.h"
#include "utils/logger/Logger.h"

#include <LittleFS.h>


WebServer::WebServer(WebSocketManager& webSocket, StorageManager& storageManager)
    : 
    webSocketManager_(webSocket),
    storageManager_(storageManager)
{
}

void WebServer::begin()
{
    registerRoutes();

    server_.serveStatic("/", LittleFS, "/");

    webSocketManager_.begin(server_);

    server_.begin();

    LOG_INFO("HTTP server started.");
}

void WebServer::registerRoutes()
{
    server_.on("/", HTTP_GET, 
        [](AsyncWebServerRequest* request)
        {
            request->send(LittleFS, "/index.html", "text/html");
        });

    server_.on("/experiments/exp001.csv", HTTP_GET,
        [this](AsyncWebServerRequest* request)
        {
            handleDownloadCsv(request);
        }
);
}

void WebServer::handleDownloadCsv(AsyncWebServerRequest* request)
{
    File file = storageManager_.historyFile();

    if (!file)
    {
        LOG_ERROR("Failed to open history CSV file.");
        request->send(404, "text/plain", "History file not found.");
        return;
    }

    request->send(file, "/experiments/exp001.csv", "text/csv", true);
}

