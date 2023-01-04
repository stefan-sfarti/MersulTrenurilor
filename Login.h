//
// Created by stefan on 02.01.2023.
//

#ifndef TRIAL_LOGIN_H
#define TRIAL_LOGIN_H
#include <iostream>
#include "common.h"
#include "sha256.h"
#include "DbCon.h"

class Login {
public:
    bool RegisterAccount(DbCon &dbCon, MYSQL *con, std::string username, std::string password);
    bool LoginAccount (DbCon &dbCon, MYSQL *con, std::string username, std::string password);
};


#endif //TRIAL_LOGIN_H
