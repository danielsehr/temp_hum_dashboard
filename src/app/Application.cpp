#include "Application.h"
#include "config/Config.h"
#include "utils/logger/Logger.h"

#include <LittleFS.h>


// public
Application::Application()
    : 
    webServer_(webSocketManager_),
    dashboardService_(webSocketManager_)
{
}


void Application::begin()
{
    Logger::begin();
    
    initializeFileSystem();
    
    networkManager_.begin();
    
    webServer_.begin();
    
    sensorService_.begin();

    LOG_INFO("Application started.");
}


void Application::initializeFileSystem()
{
    if (!LittleFS.begin(true))
    {
        LOG_ERROR("Failed to mount LittleFS.");
        return;
    }

    LOG_INFO("LittleFS mounted.");
}


void Application::update()
{
    sensorService_.update();

    if (sensorService_.hasNewMeasurement())
    {
        dashboardService_.publishMeasurement(sensorService_.latestMeasurement());
    };

    if (webSocketManager_.hasNewClient())
    {
        dashboardService_.publishHistory(*webSocketManager_.newClient());

        webSocketManager_.clearNewClient();
    }

    sensorService_.clearNewMeasurement();
}