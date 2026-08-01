#pragma once

#include "state/SensorData.h"
#include "web/WebSocketManager/WebSocketManager.h"


class DashboardService
{
public: 
    explicit DashboardService(WebSocketManager& socket);

    void publishMeasurement(const SensorData& data);

private:
    WebSocketManager& webSocketManager_;
};