//
// Created by stefan on 30.12.2022.
//

#ifndef TRIAL_DBCON_H
#define TRIAL_DBCON_H
#include "mysql/mysql.h"
#include "string"

class DbCon {
private:
    const char *server{"localhost"};
    const char *user{"stefan"};
    const char *password{"Entombed5800*"};
    const char *database{"STUDENT"};
public:
    MYSQL *connection_setup();
    MYSQL_RES *mysql_execute_query(MYSQL *connection, const char *sql_query);
    std::string GetTrainsToday(MYSQL *con);
    std::string GetArrivals(MYSQL *con);
    std::string GetDepartures(MYSQL *con);
    void AddAccount(MYSQL *con, std::string username, std::string password);
    bool CheckUserDetails(MYSQL *con, std::string username, std::string password);
    bool CheckUsername(MYSQL *con, std::string username);
};


#endif //TRIAL_DBCON_H
