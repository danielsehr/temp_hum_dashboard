#pragma once

#include "config/Config.h"
#include "state/SensorData.h"
#include "web/WebSocketManager/WebSocketManager.h"
#include "utils/RingBuffer/RingBuffer.h"


class DashboardService
{
public: 
    explicit DashboardService(WebSocketManager& socket);

    void publishMeasurement(const SensorData& data);

private:
    WebSocketManager& webSocketManager_;

    RingBuffer<SensorData, Config::RING_BUFFER_SIZE> history_;
};