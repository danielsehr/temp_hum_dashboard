#include "StorageManager.h"

void StorageManager::begin()
{
    initializeFileSystem();
}

void StorageManager::initializeFileSystem()
{
    if (!LittleFS.begin(true))
    {
        LOG_ERROR("Failed to mount LittleFS.");
        return;
    }

    if (!LittleFS.exists("/experiments"))
    {
        if (!LittleFS.mkdir("/experiments"))
        {
            LOG_ERROR("Failed to create experiments directory.");
            return;
        }
    }

    LOG_INFO("LittleFS mounted.");
}

bool StorageManager::appendMeasurement(const SensorData& measurement)
{
    File file = LittleFS.open(HISTORY_FILE, FILE_APPEND);

    if (!file)
    {
        LOG_ERROR("Failed to open csv file.");
        return false;
    }

    serializeMeasurementCsv(file, measurement);

    file.close();

    LOG_INFO("Wrote measurement to csv.");

    return true;
}

void StorageManager::serializeMeasurementCsv(File& file, const SensorData& measurement)
{
    file.print(measurement.timestamp);
    file.print(',');
    
    file.print(measurement.temperatureCelcius);
    file.print(',');
    
    file.print(measurement.humidityPercent);
    file.print(',');
    
    file.println(measurement.valid);
}

File StorageManager::historyFile()
{
    return LittleFS.open(HISTORY_FILE, FILE_READ);
}
