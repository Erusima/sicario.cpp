#include <string>
#include <cstring>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <queue>
#include "platform.h"

enum SIC_ERROR {
    SIC_NO_ERROR=0,
    SIC_INVALID_COMMAND
};

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
        std::queue<SIC_ERROR> errorQueue;

        unsigned int connInterval;
    private:
        struct sockaddr_in connAddress;
        int conn=0;
};

std::string executeCommand(std::string cmd);
