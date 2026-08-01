#pragma once

#include "web/HTTP/WebServer.h"


class Application
{
public:
    void begin();
    
    void initializeFileSystem();
    
    void update();

private:
    WebServer webServer;

    void initializeAP();
};
