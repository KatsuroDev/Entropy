#include "Logger.h"

// TODO: Will use spdlog later
#include <iostream>

namespace Entropy {

    void Logger::Trace(const char* msg)
    {
        std::cout << msg << '\n';
    }

    void Logger::Info(const char* msg)
    {
        std::cout << "[Info]: " << msg << '\n';
    }

    void Logger::Warn(const char* msg)
    {
        std::cout << "[Warning]: " << msg << '\n';
    }

    void Logger::Error(const char* msg)
    {
        std::cout << "[ERROR]: " << msg << '\n';
    }

    void Logger::FATAL(const char* msg, int code)
    {
        std::cout << "[FATAL ERROR]: " << msg << '\n';
        exit(code);
    }
}
