#include "DashboardService.h"


DashboardService::DashboardService(WebSocketManager& socket)
    : webSocketManager_(socket)
{
}


void DashboardService::publish(const SensorData& data)
{
    JsonDocument json;

    json["timestamp"] = data.timestamp;
    json["humidity"] = data.humidityPercent;
    json["temperature"] = data.temperatureCelcius;

    char buffer[128];

    serializeJson(json, buffer, sizeof(buffer));

    webSocketManager_.broadcast(buffer);
}