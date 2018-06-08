#ifndef ERRORS_H
#define ERRORS_H
#include <string>

typedef struct {
    bool critical;
    std::string text;
} ErrorType;

const ErrorType errorList[] = {
    {false, "DEBUG: Invalid Error\n"},
    {false, "ERROR: Invalid Command\n"},
    {false, "ERROR: Wrong Sicario Signature\n"}
};

#endif
