//
// Created by stefan on 02.01.2023.
//

#include "Thread.h"
#include "DbCon.h"
#include "common.h"


void Thread :: run () {
    DbCon dbCon;
    MYSQL *con = dbCon.connection_setup();
    std::string message = dbCon.GetTrainsToday(con);
    int req;
    char buffer[1024];

    write ( this->clientSocket, message.c_str(), message.length() );

    read ( this->clientSocket, & buffer, sizeof (buffer) );
    std::cout << "Received request: " << buffer << std::endl;

    req = static_cast<int>(buffer[0]);
    buffer[0] = '\0';
    switch ( req ) {
        case Arrivals:
            message = dbCon.GetArrivals(con);
            break;
        case Departures:
            message = dbCon.GetDepartures(con);
            break;
        default: message = "Bad input!";
    }
    write ( this->clientSocket, message.c_str(), message.length() );
    std::string arrivals = dbCon.GetArrivals(con);
    std::cout << "Arrivals: " << std::endl << arrivals << std::endl;
    std::string departures = dbCon.GetDepartures(con);
    std::cout << "Departures: " << std::endl << departures << std::endl;
}
