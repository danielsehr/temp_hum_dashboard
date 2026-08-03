#include "DashboardService.h"

DashboardService::DashboardService(WebSocketManager& socket) : webSocketManager_(socket)
{
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

void DashboardService::publishMeasurement(const SensorData& data)
{
    history_.push(data);

    char buffer[128];

    serializeMeasurement(data, buffer, sizeof(buffer));

    webSocketManager_.broadcast(buffer);
}

void DashboardService::publishHistory(AsyncWebSocketClient& client)
{
    char buffer[128];

    for (size_t i = 0; i < history_.size(); i++)
    {
        const auto& measurement = history_.at(i);

        serializeMeasurement(measurement, buffer, sizeof(buffer));
        
        webSocketManager_.send(client, buffer);
    }
}