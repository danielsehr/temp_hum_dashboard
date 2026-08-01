#include "DashboardService.h"


DashboardService::DashboardService(WebSocketManager& socket)
    : webSocketManager_(socket)
{
}


void DashboardService::publishMeasurement(const SensorData& data)
{
    history_.push(data);

    
    JsonDocument json;

    json["type"] = "sensor";

    JsonObject values = json["data"].to<JsonObject>();

    values["timestamp"] = data.timestamp;
    values["humidity"] = data.humidityPercent;
    values["temperature"] = data.temperatureCelcius;

    
    char buffer[128];

    serializeJson(json, buffer, sizeof(buffer));

    webSocketManager_.broadcast(buffer);
}