#include "Logger.h"

// TODO: Will use spdlog later
#include <iostream>

namespace Entropy {

    void Logger::Trace(const char* msg)
    {
        std::cout << msg << '\n';
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
        std::cout << msg << '\n';
    }

    void Logger::Warn(const char* msg)
    {
        std::cout << "[Warning]: " << msg << '\n';
    }

    void Logger::Warn(std::string msg)
    {
        std::cout << msg << '\n';
    }

    void Logger::Error(const char* msg)
    {
        std::cout << "[ERROR]: " << msg << '\n';
    }

    void Logger::Error(std::string msg)
    {
        std::cout << msg << '\n';
    }

    void Logger::FATAL(const char* msg, int code)
    {
        std::cout << "[FATAL ERROR]: " << msg << '\n';

        std::cin.get();

        exit(code);
    }

    void Logger::FATAL(std::string msg, int code)
    {
        std::cout << "[FATAL ERROR]: " << msg << '\n';

        std::cin.get();

        exit(code);
    }
}
