//
// Created by stefan on 02.01.2023.
//

#ifndef TRIAL_LOGIN_H
#define TRIAL_LOGIN_H
#include <iostream>
#include "common.h"
#include "sha256.h"
#include "DbHandler.h"

class Login {
public:
    bool RegisterAccount(DbHandler &dbCon, MYSQL *con, std::string &username, std::string &password) const;
    bool LoginAccount (DbHandler &dbCon, MYSQL *con, std::string &username, std::string &password) const;
};


#endif //TRIAL_LOGIN_H
