//
// Created by stefan on 05.01.2023.
//

#ifndef MERSULTRENURILOR_CLIENT_H
#define MERSULTRENURILOR_CLIENT_H
#include "common.h"
#include <iostream>
#include "string.h"
class Client{
private:
    int s = socket (AF_INET, SOCK_STREAM, 0);
    sockaddr_in servAddr;
    bool IsLoggedIn{false};
public:
    void Run();
    void Login();
    bool GetClientStatus();
    void GetTrainData();
    void Stop();
};
#endif //MERSULTRENURILOR_CLIENT_H
