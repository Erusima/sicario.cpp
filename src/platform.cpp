#include "platform.h"

std::string executeCommand(std::string cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string getSystem() {
    #ifdef __linux__
    return "Linux";
    #elif _WIN32
    return "Windows";
    #else
    #error Platform Not Supported!
    #endif
}

std::string getArchitecture() {
    #ifdef __linux__
    return executeCommand("uname -m");
    #else
    #error Platform Not Supported!
    #endif
}

