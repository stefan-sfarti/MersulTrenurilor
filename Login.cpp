//
// Created by stefan on 02.01.2023.
//

#include "Login.h"

bool Login::RegisterAccount(DbHandler &dbCon, MYSQL *con, std::string &username, std::string &password) const {
    if (dbCon.CheckUsername(con, username) && password.length() > 6) {
        dbCon.AddAccount(con, username, password);
        std::cout << "Registration successful" << std::endl;
        return true;
    }else {
        std::cout << "Registration failed" << std::endl;
        return false;
    }
}

bool Login::LoginAccount(DbHandler &dbCon, MYSQL *con, std::string &username, std::string &password) const{
    if (dbCon.CheckUserDetails(con, username, password)){
        return true;
    }else {
        return false;
    }
}
