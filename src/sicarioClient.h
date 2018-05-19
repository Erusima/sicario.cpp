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

class SicarioClient {
    public:
        SicarioClient(std::string serverAddress, short port);
        ~SicarioClient();

        void sendPacket(std::string data);
        std::string receivePacket();
        void sendData(std::string data);
        std::string receiveData();

        std::string registerUser();
        std::string returnUserKey();
    private:
        std::string userKey;
        struct sockaddr_in connAddress;
        int conn=0;
};
