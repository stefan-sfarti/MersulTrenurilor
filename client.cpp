#include "client.h"

void Client::Run() {
    this->servAddr.sin_port = htons(port);
    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int n = connect (this->s, reinterpret_cast < sockaddr * > ( & this->servAddr ), sizeof ( this->servAddr) );
    if (n < 0){
        std::cout << "Error connecting to server" << std::endl;
    }
    std::cout << "Connected to server" << std::endl;
    Login();
    if (this->GetClientStatus()){
        this->GetTrainData();
    }
    this->Stop();
}

void Client::Login() {
    char buffer[2048];
    char req[256];
    std::cout << "Press 1 to login or 2 to register an account" << std::endl;
    std::cin >> req;
    if (std::string(req) != "1" && std::string (req) != "2"){
        std::cout << "Wrong input" << std::endl;
        exit(1);
    }
    write(this->s, &req, sizeof req);
    memset(req, 0, sizeof(req));
    std::cout << "Enter your username: " << std::endl;
    std::cin >> req;
    write(this->s, &req, sizeof req);
    memset(req, 0, sizeof(req));
    std::cout << "Enter your password: " << std::endl;
    std::cin >> req;
    write(this->s, &req, sizeof req);
    read ( this->s, &buffer, sizeof buffer);
    std::string message = std::string (buffer);
    if (message.length() == 17){
        std::cout << message << std::endl;
        this->IsLoggedIn = true;
    }else if (message.length() == 14){
        std::cout << message.substr(0, 13) << std::endl;
        this->IsLoggedIn = false;
    }

}

bool Client::GetClientStatus() {
    return this->IsLoggedIn;
}

void Client::GetTrainData() {
    char buffer[2048];
    char req[256];
    std::cout << "Displaying trains for today: " << std::endl;
    read ( this->s, & buffer, sizeof (buffer) );
    std :: cout << buffer << '\n';

    std::cout << "Press 1 to get information about arrivals in the next hour" << std::endl;
    std::cout << "Press 2 to get information about departures in the next hour" << std::endl;

    std::cin >> req;
    if (std::string(req) != "1" && std::string (req) != "2"){
        std::cout << "Wrong input" << std::endl;
        exit(1);
    }
    write ( this->s, & req, sizeof (req) );
    memset(buffer, 0, sizeof(buffer));
    read ( this->s, & buffer, sizeof (buffer) );
    std::cout << buffer << '\n';
}

void Client::Stop() {
    close(this->s);
}




int main () {
    Client c;
    c.Run();
    return 0;

}