#pragma once


class Logger
{
public:

    static void begin();

    static void info(const char* message);

    static void warning(const char* message);

    static void error(const char* message);
};


#define LOG_INFO(msg) Logger::info(msg)
#define LOG_WARNING(msg) Logger::warning(msg)
#define LOG_ERROR(msg) Logger::error(msg)
