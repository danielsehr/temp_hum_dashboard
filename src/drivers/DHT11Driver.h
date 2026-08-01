#pragma once

#include <DHT.h>

#include "state/SensorData.h"


class DHT11Driver
{
public:
    DHT11Driver(uint8_t);

    void begin();

    SensorData read();

private:
    DHT dht;
};
