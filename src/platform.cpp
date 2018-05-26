#include "platform.h"

std::string getSystem() {
    #ifdef __linux__
    return "Linux";
    #elif _WIN32
    return "Windows";
    #else
    #error Platform Not Supported!
    #endif
}
