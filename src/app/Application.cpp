# include "Application.h"

#include <LittleFS.h>
# include <logger/Logger.h>


void Application::begin()
{
    Logger::begin();

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
    // Service comes later
}