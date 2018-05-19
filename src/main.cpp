#include <iostream>
#include <string>
#include <stdlib.h>

#include "sicarioClient.h"

const std::string msg_copyright = "Sicario_CPP // 2018 // Made by Erusima and Dante383\n\n";

int main(int argc, char** argv) {
    std::cout << msg_copyright;
    SicarioClient client(argv[1], 7319);
    std::cout << client.registerUser();
}

