#pragma once

#include "StorageManager.h"
#include "utils/logger/Logger.h"
#include "state/SensorData.h"

#include <LittleFS.h>


class StorageManager
{
public:
    void begin();

    bool appendMeasurement(const SensorData& measurement);

private:
    void initializeFileSystem();

    void serializeMeasurementCsv(File& file, const SensorData& measurement);

    static constexpr char HISTORY_FILE[] = "/experiments/exp001.csv";
};