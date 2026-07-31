#pragma once

#include "config/Config.h"

#include <ESPAsyncWebServer.h>


class WebServer
{
public:

    void begin();


private:

    AsyncWebServer server{Config::HHTP_PORT};

    void registerRoutes();
};
