#include "Application.h"
#include "utils/logger/Logger.h"


Application::Application()
    : 
    webServer_(webSocketManager_, storageManager_),
    dashboardService_(webSocketManager_)
{
}

void Application::begin()
{
    Logger::begin();
    
    storageManager_.begin();
    
    networkManager_.begin();
    
    webServer_.begin();
    
    sensorService_.begin();

    LOG_INFO("Application started.");
}

void Application::update()
{
    sensorService_.update();

    if (sensorService_.hasNewMeasurement())
    {
        dashboardService_.publishMeasurement(sensorService_.latestMeasurement());
    }

    if (webSocketManager_.hasNewClient())
    {
        dashboardService_.publishHistory(*webSocketManager_.newClient());

        webSocketManager_.clearNewClient();
    }

    sensorService_.clearNewMeasurement();
}