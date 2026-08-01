# include "Logger.h"

# include <Arduino.h>


void Logger::begin()
{
    Serial.begin(115200);
}


void Logger::info(const char* message)
{
    Serial.print("[INFO] ");
    Serial.println(message);
}


void Logger::info(const SensorData& data)
{
    Serial.print("[INFO] ");
    
    char buffer[128];

    snprintf(
        buffer,
        sizeof(buffer),
        "Timestamp: %d\n"
        "Temperature: %.1f °C\n"
        "Humidity: %.1f%%\n"
        "Valid: %s",
        data.timestamp,
        data.temperatureCelcius,
        data.humidityPercent,
        data.valid ? "true" : "false"
    );

    Serial.println(buffer);
}


void Logger::warning(const char* message)
{
    Serial.print("[WARNING] ");
    Serial.println(message);
}


void Logger::error(const char* message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}