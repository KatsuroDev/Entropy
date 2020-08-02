#include "Logger.h"

// TODO: use spdlog
#include <iostream>

namespace Entropy {

    void Logger::Trace(const char* msg)
    {
        std::cout <<  msg << '\n';
    }

    void Logger::Trace(std::string msg)
    {
        std::cout << msg << '\n';
    }

    void Logger::Info(const char* msg)
    {
        std::cout << "[Info]: " << msg << '\n';
    }

    void Logger::Info(std::string msg)
    {
        std::cout << "[Info]: " << msg << '\n';
    }

    void Logger::Warn(const char* msg)
    {
        std::cout << "[Warning]: " << msg << '\n';
    }

    void Logger::Warn(std::string msg)
    {
        std::cout << "[Warning]: " << msg << '\n';
    }

    void Logger::Error(const char* msg)
    {
        std::cout << "[AN ERROR OCCURRED]: " << msg << '\n';
    }

    void Logger::Error(std::string msg)
    {
        std::cout << "[AN ERROR OCCURRED]: " << msg << '\n';
    }
}
