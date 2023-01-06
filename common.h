#ifndef __TRIAL_COMMON_H__
#define __TRIAL_COMMON_H__

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <string.h>
#include "mysql/mysql.h"

constexpr unsigned short int port = 49500;

enum ReqType{
    Arrivals = '1',
    Departures = '2',
};

#endif //__TRIAL_COMMON_H__
