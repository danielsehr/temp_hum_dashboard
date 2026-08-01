#include "SensorService.h"
#include "config/Pins.h"
#include "config/Config.h"
#include "logger/Logger.h"


SensorService::SensorService() 
    : driver(Pins::DHT) 
{
}


void SensorService::begin()
{
    driver.begin();
}


void SensorService::update()
{
    if (millis() - lastRead < Config::SENSOR_UPDATE_MS)
        return;

    lastRead = millis();

    
    SensorData measurement = driver.read();

    if (!measurement.valid)
    {
        LOG_WARNING("Invalid sensor reading.");

        return;
    }

    latest = measurement;

    LOG_INFO("Sensor updated.\n");
    LOG_INFO(latest);
}


const SensorData& SensorService::latestMeasurement() const
{
    return latest;
}
