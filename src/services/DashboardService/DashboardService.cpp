#include "DashboardService.h"


DashboardService::DashboardService(WebSocketManager& socket)
    : socket_(socket)
{
}


void DashboardService::publish(const SensorData& data)
{
    StaticJsonDocument<128> json;

    json["timestamp"] = data.timestamp;
    json["humidity"] = data.humidityPercent;
    json["temperature"] = data.temperatureCelcius;

    char buffer[128];

    serializeJson(json, buffer, sizeof(buffer));

    socket_.broadcast(buffer);
}