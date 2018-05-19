#include "sicarioClient.h"

SicarioClient::SicarioClient(std::string serverAddress, short port) {
    conn = socket(AF_INET, SOCK_STREAM, 0);
    memset(&connAddress, 0, sizeof(connAddress));
    connAddress.sin_family = AF_INET;
    connAddress.sin_port = htons(port);
    inet_pton(AF_INET,serverAddress.c_str(),&connAddress.sin_addr);
    connect(conn, (struct sockaddr*)&connAddress, sizeof(connAddress));
}

SicarioClient::~SicarioClient() {
    close(conn);
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
        // TODO: Multi-packet
    }
}

std::string SicarioClient::receiveData() {
    std::string data = receivePacket();
    if(data.substr(0,4) == "SC00")
        return data.substr(3,data.length()-4);
    else {
        // TODO: Multi-packet
    }
}

std::string SicarioClient::registerUser(){
    this->sendData("register");
    std::string userKey = this->receiveData();
    userKey = userKey.substr(10,userKey.length());
    this->userKey = userKey;
    return userKey;
}

std::string SicarioClient::returnUserKey() {
    return this->userKey;
}
