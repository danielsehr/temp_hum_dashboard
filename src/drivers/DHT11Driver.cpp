#include "DHT11Driver.h"


DHT11Driver::DHT11Driver(uint8_t pin)
    : dht(pin, DHT11)
{
}

void DHT11Driver::begin()
{
    dht.begin();
}

SensorData DHT11Driver::read()
{
    SensorData data{};

    data.timestamp = millis();

    data.temperatureCelcius = dht.readTemperature();
    data.humidityPercent = dht.readHumidity();

    data.valid =
        !isnan(data.temperatureCelcius) &&
        !isnan(data.humidityPercent);

    return data;
}
