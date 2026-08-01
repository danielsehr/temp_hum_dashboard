#pragma once

#include "web/HTTP/WebServer.h"
#include "services/SensorService.h"


class Application
{
public:
    void begin();
    
    void initializeFileSystem();
    
    void update();

private:
    WebServer webServer;

    SensorService sensorService;

    void initializeAP();
};
