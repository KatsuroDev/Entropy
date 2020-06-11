#include "Log.h"

// Temporairy include
// TODO: Will use spdlog later
#include <iostream>

namespace Entropy {

    void Logger::Trace(const char* msg)
    {
        std::cout << msg;
    }
}
