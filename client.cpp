#include "common.h"
#include <iostream>
#include "string.h"

int main () {

    int s = socket (AF_INET, SOCK_STREAM, 0);
    sockaddr_in servAddr;
    servAddr.sin_port = htons(port);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = connect (s, reinterpret_cast < sockaddr * > ( & servAddr ), sizeof ( servAddr) );
    if (n < 0){
        std::cout << "Error connecting to server" << std::endl;
    }
    std::cout << "Connected to server" << std::endl;

    char buffer[2048];
    char req[256];
    std::cout << "Displaying trains for today: " << std::endl;
    read ( s, & buffer, sizeof (buffer) );
    std :: cout << buffer << '\n';

    std::cout << "Press 1 to get information about arrivals in the next hour" << std::endl;
    std::cout << "Press 2 to get information about departures in the next hour" << std::endl;

    std::cin >> req;
    if (std::string(req) != "1" && std::string (req) != "2"){
        std::cout << "Wrong input" << std::endl;
        close(s);
        return 0;
    }
    write ( s, & req, sizeof (req) );
    memset(buffer, 0, sizeof(buffer));
    read ( s, & buffer, sizeof (buffer) );
    std::cout << buffer << '\n';

    close(s);
    return 0;
}