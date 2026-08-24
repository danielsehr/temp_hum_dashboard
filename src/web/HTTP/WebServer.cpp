#include "WebServer.h"
#include "utils/logger/Logger.h"

#include <LittleFS.h>


WebServer::WebServer(
    WebSocketManager& webSocket, 
    StorageManager& storageManager, 
    ExperimentService& experimentService
): 
    webSocketManager_(webSocket),
    storageManager_(storageManager),
    experimentService_(experimentService)
{
}

void WebServer::begin()
{
    registerRoutes();

    server_.serveStatic("/", LittleFS, "/");

    webSocketManager_.begin(server_);

    server_.begin();

    LOG_INFO("HTTP server started.");
}

void WebServer::registerRoutes()
{
    server_.on("/", HTTP_GET, 
        [](AsyncWebServerRequest* request)
        {
            request->send(LittleFS, "/index.html", "text/html");
        });

    server_.on("/api/experiment/start", HTTP_POST,
        [this](AsyncWebServerRequest* request)
        {
            handleStartExperiment(request);
        });

    server_.on("/api/experiment/stop", HTTP_POST,
        [this](AsyncWebServerRequest* request)
        {
            handleStopExperiment(request);
        });

    server_.on("/api/experiment/status", HTTP_GET,
        [this](AsyncWebServerRequest* request)
        {
            handleExperimentStatus(request);
        });

    server_.on("/api/experiment/download", HTTP_GET,
        [this](AsyncWebServerRequest* request)
        {
            handleDownloadCsv(request);
        });
}


void WebServer::handleStartExperiment(AsyncWebServerRequest* request)
{
    if (!experimentService_.start(nullptr))
    {
        request->send(409, "text/plain", "Could not start experiment.");
        return;
    }

    request->send(200, "text/plain", "Experiment started.");
}

void WebServer::handleStopExperiment(AsyncWebServerRequest* request)
{
    experimentService_.stop();

    request->send(200, "text/plain", "Experiment stopped.");
}

void WebServer::handleExperimentStatus(AsyncWebServerRequest* request)
{
    const bool recording = experimentService_.isRecording();

    if (recording)
    {
        request->send(200, "application/json", R"({"recording":true})");
    } 
    else 
    {
        request->send(200, "application/json", R"({"recording":false})");
    }
}

void WebServer::handleDownloadCsv(AsyncWebServerRequest* request)
{
    const Experiment& experiment = experimentService_.currentExperiment();

    char path[Config::CSV_PATH_MAX];

    if(!storageManager_.createCsvPath(experiment, path))
    {
        LOG_ERROR("Failed to generate experiment CSV path.");
        request->send(500, "text/plain", "Failed to generate file path.");
        return;
    }
    
    File file = LittleFS.open(path, FILE_READ);

    if (!file)
    {
        LOG_ERROR("Failed to open experiment CSV file:");
        LOG_ERROR(path);
        request->send(404, "text/plain", "Experiment file not found.");
        return;
    }

    request->send(file, path, "text/csv", true);
}

