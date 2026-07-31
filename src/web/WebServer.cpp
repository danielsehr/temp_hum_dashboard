#include "WebServer.h"
#include "logger/Logger.h"

#include <LittleFS.h>


void WebServer::begin()
{
    registerRoutes();

    server.begin();

    LOG_INFO("HTTP server started.");
}


void WebServer::registerRoutes()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/index.html", "text/html");
    });
}