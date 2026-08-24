#pragma once

#include "storage/StorageManager.h"
#include "network/NetworkManager.h"
#include "web/HTTP/WebServer.h"
#include "services/SensorService/SensorService.h"
#include "services/DashboardService/DashboardService.h"
#include "services/ExperimentService/ExperimentService.h"


class Application
{
public:
    Application();

    void begin();
    
    void update();

private:
    StorageManager storageManager_;

    NetworkManager networkManager_; 

    WebSocketManager webSocketManager_;
    
    SensorService sensorService_;
    
    ExperimentService experimentService_;
    
    DashboardService dashboardService_;
    
    WebServer webServer_;
};
