#pragma once

#include "drivers/DHT11Driver.h"


class SensorService
{
public:
    SensorService();

    void begin();
    
    void update();
    
    const SensorData& latestMeasurement() const;

private:
    DHT11Driver driver_;

    SensorData latest_;

    uint32_t lastRead_ = 0;
};