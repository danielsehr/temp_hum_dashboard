#include "SensorService.h"
#include "config/Pins.h"
#include "config/Config.h"
#include "logger/Logger.h"


SensorService::SensorService() 
    : driver_(Pins::DHT) 
{
}


void SensorService::begin()
{
    driver_.begin();
}


void SensorService::update()
{
    if (millis() - lastRead_ < Config::SENSOR_UPDATE_MS)
        return;

    lastRead_ = millis();

    
    SensorData measurement = driver_.read();

    if (!measurement.valid)
    {
        LOG_WARNING("Invalid sensor reading.");

        return;
    }

    latest_ = measurement;

    LOG_INFO("Sensor updated.\n");
    LOG_INFO(latest_);
}


const SensorData& SensorService::latestMeasurement() const
{
    return latest_;
}
