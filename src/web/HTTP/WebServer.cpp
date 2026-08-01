#include "WebServer.h"
#include "logger/Logger.h"

#include <LittleFS.h>


WebServer::WebServer(WebSocketManager& webSocket)
    : webSocketManager_(webSocket)
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
    server_.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/index.html", "text/html");
    });
}