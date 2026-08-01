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
    DHT11Driver driver;

    SensorData latest;

    uint32_t lastRead = 0;
};