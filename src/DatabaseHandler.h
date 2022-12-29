//
// Created by stefan on 25.12.2022.
//

#ifndef MERSULTRENURILOROOP_DATABASEHANDLER_H
#define MERSULTRENURILOROOP_DATABASEHANDLER_H
#include "mysql/mysql.h"
#include "string"

class DatabaseHandler {
private:

public:
    MYSQL *con;
    //MySql connection handling
    static MYSQL *mysql_connection_setup(const char *server, const char *user, const char *password, const char *database);
    MYSQL_RES *mysql_execute_query(MYSQL *connection, const char *sql_query);
    //Retrieve data from database
    std::string GetTrainsToday(MYSQL *con);
    std::string GetArrivals(MYSQL *con);
    std::string GetDepartures(MYSQL *con);
    void AddAccount(MYSQL *con,std::string username, std::string password);
    //Constructor
    DatabaseHandler();
};


#endif //MERSULTRENURILOROOP_DATABASEHANDLER_H
