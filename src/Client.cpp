#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

int main(int argc, char *argv[])
{
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_aton("127.0.0.1", &serv_addr.sin_addr);
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR connecting to server" << std::endl;
        return 1;
    }
    while (true){

        //write data to server
        char buffer[1024];
        std::string message;
        std::cout<<"Press 1 to Login"<<std::endl;
        std::cout<<"Press 2 to Register"<<std::endl;
        std::cin >> message;
        int n = send(sockfd, message.c_str(), message.length() - 1, MSG_DONTWAIT);
        if (n < 0) {
            std::cerr << "ERROR writing to socket" << std::endl;
            exit(1);
        }
        // Read data from the server
        n = recv(sockfd, buffer, 1023, MSG_DONTWAIT);
        if (n < 0)
        {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        }
        buffer[n] = '\0';
        std::cout << "Received message from server: " << buffer << std::endl;
    }
    // Write data to the server

    // Close the socket
    close(sockfd);

    return 0;
}