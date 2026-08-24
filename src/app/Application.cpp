#include "Application.h"
#include "utils/logger/Logger.h"


Application::Application()
    : 
    storageManager_(),
    networkManager_(),
    webSocketManager_(),
    sensorService_(),
    experimentService_(storageManager_),
    dashboardService_(webSocketManager_),
    webServer_(webSocketManager_, storageManager_, experimentService_)
{
}

void Application::begin()
{
    Logger::begin();
    
    storageManager_.begin();
    
    networkManager_.begin();
    
    webServer_.begin();
    
    sensorService_.begin();

    LOG_INFO("Application started. Printing filesystem:");

    storageManager_.listDirectory("/experiments");

    LOG_INFO("Done.");
}

void Application::update()
{
    sensorService_.update();

    if (sensorService_.hasNewMeasurement())
    {
        const SensorData& measurement = sensorService_.latestMeasurement();

        dashboardService_.publishMeasurement(measurement);

        experimentService_.record(measurement);
    }

    if (webSocketManager_.hasNewClient())
    {
        dashboardService_.publishHistory(*webSocketManager_.newClient());

        webSocketManager_.clearNewClient();
    }

    sensorService_.clearNewMeasurement();
}