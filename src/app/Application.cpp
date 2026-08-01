#include "Application.h"
#include "config/Config.h"
#include "logger/Logger.h"

#include <LittleFS.h>
#include <WiFi.h>


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

    LOG_INFO("Application started.");

    initializeFileSystem();

    initializeAP();

    webServer_.begin();

    sensorService_.begin();
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

    dashboardService_.publish(sensorService_.latestMeasurement());
}


// private
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