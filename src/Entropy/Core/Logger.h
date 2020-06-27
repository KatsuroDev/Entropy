#pragma once

#include <string>
#include <sstream>

namespace Entropy {

    class Logger
    {
    public:
        static void Trace(const char* msg);
        static void Trace(std::string msg);
        static void Info(const char* msg);
        static void Info(std::string msg);
        static void Warn(const char* msg);
        static void Warn(std::string msg);
        static void Error(const char* msg);
        static void Error(std::string msg);
        static void FATAL(const char* msg, int code = 0);
        static void FATAL(std::string msg, int code = 0);
    };
}

#if _DEBUG
#define NT_TRACE(...) Logger::Trace(__VA_ARGS__)
#define NT_INFO(...) Logger::Info(__VA_ARGS__)
#define NT_WARN(...) Logger::Warn(__VA_ARGS__)
#define NT_ERROR(...) Logger::Error(__VA_ARGS__)
#define NT_FATAL(...) Logger::FATAL(__VA_ARGS__)
#else
#define NT_TRACE(...)
#define NT_INFO(...) Logger::Info(__VA_ARGS__)
#define NT_WARN(...) Logger::Warn(__VA_ARGS__)
#define NT_ERROR(...) Logger::Error(__VA_ARGS__)
#define NT_FATAL(...) Logger::FATAL(__VA_ARGS__)
#endif
