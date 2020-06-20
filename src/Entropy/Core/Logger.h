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
