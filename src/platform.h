#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <sys/types.h>
#include <unistd.h>

std::string executeCommand(std::string cmd);
std::string getSystem();
std::string getArchitecture();
bool isRoot();
unsigned long long getRAM();

#endif
