#pragma once

#include "web/HTTP/WebServer.h"
#include "services/SensorService/SensorService.h"
#include "services/DashboardService/DashboardService.h"


class Application
{
public:
    Application();

    void begin();
    
    void initializeFileSystem();
    
    void update();

private:
    WebSocketManager webSocketManager_;
    
    WebServer webServer_;

    SensorService sensorService_;

    DashboardService dashboardService_;

    void initializeAP();
};
