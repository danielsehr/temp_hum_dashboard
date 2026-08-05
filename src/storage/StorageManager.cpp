#include "StorageManager.h"
#include "utils/logger/Logger.h"

#include <LittleFS.h>


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

    LOG_INFO("LittleFS mounted.");
}