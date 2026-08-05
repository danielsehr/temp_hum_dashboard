#pragma once

#include "config/Config.h"
#include "utils/logger/Logger.h"

#include <WiFi.h>

class NetworkManager
{
public:
    void begin();
    
private:
    void initializeAP();
    
};
