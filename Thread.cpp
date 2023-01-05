//
// Created by stefan on 02.01.2023.
//

#include "Thread.h"
#include "DbHandler.h"
#include "Login.h"
#include "common.h"


void Thread :: run () {
    char buffer[1024];
    read(this->clientSocket, &buffer, sizeof buffer);
    std::cout << buffer << std::endl;
    int req = atoi(buffer);
    switch (req) {
        case 1:
            if (doLogin()){
                this->IsLoggedIn = true;
            }else
                this->IsLoggedIn = false;
            break;
        case 2:
            if (doRegister()){
                this->IsLoggedIn = true;
            }else
                this->IsLoggedIn = false;
            break;
        default:
            std::cout << "Invalid request" << std::endl;
            
    }
    if (this->IsLoggedIn){
        GetTrainData();
    }else{
        std::cout << "Not logged in" << std::endl;
    }

}

bool Thread::doLogin() const{
    char buffer[1024];
    std::string message;
    std::string username;
    std::string password;
    Login login;
    DbHandler dbCon;
    MYSQL *con = dbCon.connection_setup();

    read(this->clientSocket, &buffer, sizeof buffer);
    username = buffer;
    memset(buffer, 0, sizeof(buffer));
    read(this->clientSocket, &buffer, sizeof buffer);
    password = buffer;
    memset(buffer, 0, sizeof(buffer));
    if (login.LoginAccount(dbCon, con, username, password)) {
        message = "Login successful!";
        std::cout << message << std::endl;
        write(this->clientSocket, message.c_str(), 17);
        return true;
    } else {
        message = "Login failed!";
        std::cout << message << std::endl;
        write(this->clientSocket, message.c_str(), 13);
        return false;
    }
}

bool Thread::doRegister() const{
    char buffer[1024];
    std::string message;
    std::string username;
    std::string password;
    Login login;
    DbHandler dbCon;
    MYSQL *con = dbCon.connection_setup();

    read(this->clientSocket, &buffer, sizeof buffer);
    username = buffer;
    memset(buffer, 0, sizeof(buffer));
    read(this->clientSocket, &buffer, sizeof buffer);
    password = buffer;
    memset(buffer, 0, sizeof(buffer));
    if (login.RegisterAccount(dbCon, con, username, password)) {
        message = "Registered successfully!";
        write(this->clientSocket, message.c_str(), message.length());
        return true;
    } else {
        message = "Registration failed!";
        write(this->clientSocket, message.c_str(), message.length());
        return false;
    }
}

void Thread::GetTrainData() const {
    char buffer[1024];
    std::string message;
    DbHandler dbCon;
    MYSQL *con = dbCon.connection_setup();
    int req;
    message = dbCon.GetTrainsToday(con);

    write(this->clientSocket, message.c_str(), message.length());

    read(this->clientSocket, &buffer, sizeof(buffer));
    std::cout << "Received request: " << buffer << std::endl;
    req = static_cast<int>(buffer[0]);
    memset(buffer, 0, sizeof(buffer));
    switch (req) {
        case Arrivals:
            message = dbCon.GetArrivals(con);
            break;
        case Departures:
            message = dbCon.GetDepartures(con);
            break;
        default:
            message = "Bad input!";
    }
    write(this->clientSocket, message.c_str(), message.length());
    std::string arrivals = dbCon.GetArrivals(con);
    std::cout << "Arrivals: " << std::endl << arrivals << std::endl;
    std::string departures = dbCon.GetDepartures(con);
    std::cout << "Departures: " << std::endl << departures << std::endl;
}
