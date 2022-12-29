//
// Created by stefan on 25.12.2022.
//

#include <iostream>
#include "DatabaseHandler.h"
#include "mysql/mysql.h"
#include "../lib/sha256.h"

MYSQL *DatabaseHandler::mysql_connection_setup(const char *server, const char *user, const char *password,
                                               const char *database) {
    MYSQL *connection = mysql_init(NULL);
    if(!mysql_real_connect(connection,server, user, password, database,0,NULL,0) ) {
        std::cout<< "Connection Error:"<< mysql_error(connection)<<std::endl;
        exit(1);
    }
    return connection;
}

MYSQL_RES *DatabaseHandler::mysql_execute_query(MYSQL *connection, const char *sql_query) {
    if (mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return mysql_use_result(connection);
}

std::string DatabaseHandler::GetTrainsToday(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string message;
    res = mysql_execute_query(con, "SELECT * FROM MersulTrenurilor WHERE date(data_plecare) = curdate();");
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int j = 0; j < 10; ++j) {
            message.append(row[j]);
            message.append(" | ");
        }
    }
    mysql_free_result(res);
    return message;
}

std::string DatabaseHandler::GetArrivals(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string message;
    res = mysql_execute_query(con, "SELECT * FROM MersulTrenurilor WHERE date(data_plecare) = curdate() AND ora_sosire between curtime()+1 and curtime()+10000");
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int j = 0; j < 10; ++j) {
            message.append(row[j]);
            message.append(" | ");
        }
    }
    mysql_free_result(res);
    return message;
}

std::string DatabaseHandler::GetDepartures(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    res = mysql_execute_query(con, "SELECT * FROM MersulTrenurilor WHERE date(data_plecare) = curdate() AND ora_plecare between curtime()+1 and curtime()+10000;");
    std::string message;
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int j = 0; j < 10; ++j) {
            message.append(row[j]);
            message.append(" | ");
        }
    }
    mysql_free_result(res);
    return message;
}

void DatabaseHandler::AddAccount(MYSQL *con, std::string username, std::string password) {
    SHA256 sha256;
    std::string hashedPass = sha256(password);
    std::string query = "INSERT INTO Accounts (username,password) VALUES (\"" + username + "\"" + ",\"" + hashedPass + "\");";
    if (mysql_send_query(con, query.c_str(), query.length()) != 0){
        std::cout << "MySQL Query Error: " << mysql_error(con) << std::endl;
        exit(1);
    }
}


DatabaseHandler::DatabaseHandler() {
    con = mysql_connection_setup("localhost", "stefan", "Entombed5800*", "STUDENT");

}



