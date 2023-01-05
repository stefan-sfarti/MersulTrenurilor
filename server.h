//
// Created by stefan on 05.01.2023.
//

#ifndef MERSULTRENURILOR_SERVER_H
#define MERSULTRENURILOR_SERVER_H
#include <thread>
#include "common.h"
#include "DbHandler.h"
#include "mysql/mysql.h"
#include "Thread.h"
class Server {
private:
    int lSocket = socket (AF_INET, SOCK_STREAM, 0);
    int optValue = 1;
    sockaddr_in servAddrCfg;

public:
    void run ();
};


#endif //MERSULTRENURILOR_SERVER_H
