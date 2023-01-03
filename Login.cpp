//
// Created by stefan on 02.01.2023.
//

#include "common.h"
#include "Login.h"
bool Login::CheckUsername(std::string username) {
    MYSQL_RES *res;
    std::string query = "SELECT username FROM Accounts WHERE username =" + username +";";
    res = databaseHandler2.mysql_execute_query(databaseHandler2.con, query.c_str());
    if (res != NULL){
        return false;
    }else return true;
}


bool Login::CheckPassword(std::string password) {
    if (password.length() < 6){
        std::cout << "Password too short" << std::endl;
        return false;
    }else return true;
}


bool Login::RegisterAccount(std::string username, std::string password) {
    if (CheckUsername(username) && CheckPassword(password)){
        SHA256 sha256;
        std::string hashedPass = sha256(password);
        std::string query = "INSERT INTO Accounts (username, password) VALUES (\"" + username + "\", \"" + hashedPass + "\");";
        if (mysql_send_query(databaseHandler2.con, query.c_str(), query.length()) != 0){
            std::cout << "MySQL Query Error: " << mysql_error(databaseHandler2.con) << std::endl;
            exit(1);
        }
        return true;
    }else {
        std::cout << "Registration failed" << std::endl;
        return false;
    }
}