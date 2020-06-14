#include "Logger.h"

// Temporairy include
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

    void Logger::Fatal(const char* msg)
    {
        std::cout << "[FATAL ERROR]: " << msg << '\n';
    }
}
