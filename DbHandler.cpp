//
// Created by stefan on 30.12.2022.
//
#include "common.h"
#include "DbHandler.h"
#include "sha256.h"

MYSQL *DbHandler::connection_setup() {
    MYSQL *con = mysql_init(nullptr);
    if (!mysql_real_connect(con, this -> server, getenv("_MYSQLUSER"), getenv("_MYSQLPASS"), this -> database, 0, nullptr, 0) ) {
        std::cout << "Connection to Database failed:" << mysql_error(con) << std::endl;
        throw 1;
    }
    return con;
}

MYSQL_RES *DbHandler::mysql_execute_query(MYSQL *connection, const char *sql_query) {
    if (mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return mysql_use_result(connection);
}

std::string DbHandler::GetTrainsToday(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string message;
    unsigned int num_fields;
    res = mysql_execute_query(con, "SELECT * FROM MersulTrenurilor WHERE DATE(data_plecare) = CURDATE() OR DATE(data_sosire) = CURDATE();");
    num_fields = mysql_num_fields(res);
    int counter{0};
    while ((row = mysql_fetch_row(res)) != nullptr) {
        for (int j = 0; j < num_fields; ++j) {
            message.append(row[j]);
            message.append(" | ");

            if (j % 8 == 0 && j % 16 != 0){
                message.append("\n");
            }
        }
        counter++;
    }
    std::cout << "Rows processed: " << counter << std::endl;
    mysql_free_result(res);
    if (message.length() == 0){
        message = "No trains today";
    }
    return message;
}

std::string DbHandler::GetArrivals(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string message;
    res = mysql_execute_query(con, "SELECT id_tren, plecare, ora_plecare, sosire, ora_sosire, intarzieri FROM MersulTrenurilor WHERE data_sosire = CURDATE() AND ora_sosire BETWEEN CURTIME() AND DATE_ADD(CURTIME(), INTERVAL 1 HOUR);");
    unsigned int num_fields;
    num_fields = mysql_num_fields(res);
    int counter{0};

    while ((row = mysql_fetch_row(res)) != nullptr) {
        for (int j = 0; j < num_fields; ++j) {
            if (j % 5 == 0 && j % 10 != 0){
                message.append("Delay: ");
                message.append(row[j]);
                message.append(" minutes");
                message.append("\n");
            }else{
                message.append(row[j]);
                message.append(" | ");
            }
        }
        counter++;
    }
    std::cout << "Rows processed: " << counter << std::endl;
    mysql_free_result(res);
    if (message.length() == 0){
        message = "No trains arriving in the next hour";
    }
    return message;
}

std::string DbHandler::GetDepartures(MYSQL *con) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string message;
    res = mysql_execute_query(con, "SELECT id_tren, plecare, sosire, ora_plecare, ora_sosire FROM MersulTrenurilor WHERE data_plecare = CURDATE() AND ora_plecare BETWEEN CURTIME() AND DATE_ADD(CURTIME(), INTERVAL 1 HOUR);");
    unsigned int num_fields;
    num_fields = mysql_num_fields(res);
    int counter{0};

    while ((row = mysql_fetch_row(res)) != nullptr) {
        for (int j = 0; j < num_fields; ++j) {
            message.append(row[j]);
            message.append(" | ");
            if (j % 4 == 0 && j % 8 != 0){
                message.append("\n");
            }
        }
        counter++;
    }
    std::cout << "Rows processed: " <<counter << std::endl;
    mysql_free_result(res);
    if (message.length() == 0){
        message = "No trains departing in the next hour";
    }
    return message;
}

bool DbHandler::CheckUsername(MYSQL *con, std::string &username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    std::string query = "SELECT username FROM Accounts WHERE username ='" + username +"';";
    res = mysql_execute_query(con, query.c_str());
    row = mysql_fetch_row(res);
    if (row != nullptr){
        mysql_free_result(res);
        return false;
    }else {
        mysql_free_result(res);
        return true;
    }
}


bool DbHandler::CheckUserDetails(MYSQL *con, std::string &username, std::string &password) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    SHA256 sha256;
    std::string hashedPass = sha256(password);
    std::string query = "SELECT username FROM Accounts WHERE username ='" + username +"' AND password = '" +hashedPass +"';";
    res = mysql_execute_query(con, query.c_str());
    row = mysql_fetch_row(res);
    if (row != nullptr){
        mysql_free_result(res);
        return true;
    }else {
        mysql_free_result(res);
        return false;
    }
}

void DbHandler::AddAccount(MYSQL *con, std::string &username, std::string &password) const {
    SHA256 sha256;
    std::string hashedPass = sha256(password);
    std::string query = "INSERT INTO Accounts (username,password) VALUES (\"" + username + "\"" + ",\"" + hashedPass + "\");";
    if (mysql_send_query(con, query.c_str(), query.length()) != 0){
        std::cout << "MySQL Query Error: " << mysql_error(con) << std::endl;
        exit(1);
    }
}


