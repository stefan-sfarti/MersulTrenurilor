//
// Created by stefan on 25.12.2022.
//

#include <mysql/mysql.h>
#include <iostream>
#include "Login.h"
#include "DatabaseHandler.h"
#include "../lib/sha256.h"
DatabaseHandler databaseHandler1;

bool Login::CheckUsername(std::string username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string query = "SELECT username FROM Accounts WHERE username =" + username;
    res = databaseHandler1.mysql_execute_query(databaseHandler1.con, query.c_str());
    row = mysql_fetch_row(res);
    if (row[0] == username){
        return true;
    }else return false;

}

bool Login::LogIn(std::string username, std::string password) {
    if (CheckUsername(username)){
        SHA256 sha256;
        MYSQL_RES *res;
        MYSQL_ROW row;
        std::string hashedPass = sha256(password);
        std::string query = "SELECT password FROM Accounts WHERE password =" + hashedPass + "AND username =" + username;
        res = databaseHandler1.mysql_execute_query(databaseHandler1.con, query.c_str());
        row = mysql_fetch_row(res);
        if (row[0] != NULL){
            std::cout << "Logged in successfully" << std::endl;
            this -> username = username;
            return true;
        }else {
            std::cout << "Login failed!" << std::endl;
            return false;
        }
    }else return false;
}

bool Login::IsLoggedIn() {
    return loggedin;
}


