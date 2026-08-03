#include "DashboardService.h"

DashboardService::DashboardService(WebSocketManager& socket) : webSocketManager_(socket)
{
}

void DashboardService::publishMeasurement(const SensorData& data)
{
    history_.push(data);

    char buffer[128];

    serializeMeasurement(data, buffer, sizeof(buffer));

    webSocketManager_.broadcast(buffer);
}

void DashboardService::serializeMeasurement(const SensorData& data, char* buffer, std::size_t bufferSize) const
{
    JsonDocument json;

    json["type"] = "sensor";

    JsonObject values = json["data"].to<JsonObject>();

    values["timestamp"] = data.timestamp;
    values["humidity"] = data.humidityPercent;
    values["temperature"] = data.temperatureCelcius;

    serializeJson(json, buffer, bufferSize);
}