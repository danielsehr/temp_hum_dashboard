#pragma once

#include <cstdint>


struct SensorData
{
    uint32_t timestamp;

    float temperatureCelcius;
    float humidityPercent;

    bool valid;
};
