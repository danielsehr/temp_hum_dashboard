# include "Application.h"

# include <logger/Logger.h>


void Application::begin()
{
    Logger::begin();

    LOG_INFO("Application started.");
}


void Application::update()
{
    // Service comes later
}