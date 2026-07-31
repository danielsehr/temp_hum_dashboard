#pragma once

#include "web/WebServer.h"


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
