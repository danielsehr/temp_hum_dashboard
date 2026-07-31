# include "Application.h"
#include "config/Config.h"
#include "logger/Logger.h"

#include <LittleFS.h>
#include <WiFi.h>


void Application::begin()
{
    Logger::begin();

    LOG_INFO("Application started.");

    initializeFileSystem();

    initializeAP();

    webServer.begin();
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


void Application::initializeAP()
{
    LOG_INFO("Start access point...");


    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(Config::AP_NAME, Config::AP_PASSWORD))
    {
        LOG_ERROR("Failed to start AP.");
        return;
    }


    LOG_INFO("AP started.");
    LOG_INFO(WiFi.softAPIP().toString().c_str());
}