#pragma once

#include <cstdint>


namespace Config
{
    constexpr char AP_NAME[] = "Temp_Hum_Dashboard";
    constexpr char AP_PASSWORD[] = "123456789";
    constexpr uint16_t HTTP_PORT = 80;
    constexpr uint32_t SENSOR_UPDATE_MS = 5000;
    constexpr std::size_t RING_BUFFER_SIZE = 864;
} 
