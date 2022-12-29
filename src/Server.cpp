#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mysql/mysql.h>
#include "DatabaseHandler.h"
#include "Register.h"
#include "Login.h"

const int kMaxConnections = 5;
const int kPortNumber = 5000;
void* handle_client_request(void* arg) {
    int client_sock = *(int *) arg;
    DatabaseHandler databaseHandler;
    while (true) {
        char buffer[1024];
        int n = recv(client_sock, buffer, 1023, MSG_DONTWAIT);
        if (n < 0) {
            std::cerr << "ERROR reading from socket" << std::endl;
            exit(1);
        }
        std::string request(buffer);
        std::cout << "Received:" << buffer << std::endl;
        if (request == "1") {
            Login login;
            std::string message;
            char buffer[1024];
            if (!login.IsLoggedIn()) {
                message = "Enter your username:";
                int n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR writing to socket" << std::endl;
                    exit(1);
                }
                n = recv(client_sock, buffer, 1023, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR reading from socket" << std::endl;
                    exit(1);
                }
                std::string username(buffer);
                message = "Enter your password:";
                n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR writing to socket" << std::endl;
                    exit(1);
                }
                n = recv(client_sock, buffer, 1023, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR reading from socket" << std::endl;
                    exit(1);
                }
                std::string password(buffer);
                if (login.LogIn(username, password)) {
                    message = "Logged in successfully";
                    n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                    if (n < 0) {
                        std::cerr << "ERROR writing to socket" << std::endl;
                        exit(1);
                    }
                } else {
                    message = "Log in failed";
                    n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                    if (n < 0) {
                        std::cerr << "ERROR writing to socket" << std::endl;
                        exit(1);
                    }
                }

            }

        } else if (request == "2") {
            Register aRegister;
            std::string message;
            char buffer[1024];
            message = "Enter your desired username:";
            int n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
            if (n < 0) {
                std::cerr << "ERROR writing to socket" << std::endl;
                exit(1);
            }
            n = recv(client_sock, buffer, 1023, MSG_DONTWAIT);
            if (n < 0) {
                std::cerr << "ERROR reading from socket" << std::endl;
                exit(1);
            }
            std::string username(buffer);
            message = "Enter your desired password (longer than 6 characters):";
            n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
            if (n < 0) {
                std::cerr << "ERROR writing to socket" << std::endl;
                exit(1);
            }
            n = recv(client_sock, buffer, 1023, MSG_DONTWAIT);
            if (n < 0) {
                std::cerr << "ERROR reading from socket" << std::endl;
                exit(1);
            }
            std::string password(buffer);
            if (aRegister.RegisterAccount(username, password)) {
                message = "Registered successfully";
                n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR writing to socket" << std::endl;
                    exit(1);
                }
            } else {
                message = "Registration failed";
                n = send(client_sock, message.c_str(), message.length() - 1, MSG_DONTWAIT);
                if (n < 0) {
                    std::cerr << "ERROR writing to socket" << std::endl;
                    exit(1);
                }
            }

        }
        return nullptr;
    }
}


int main() {
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Bind the socket to a port
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(kPortNumber);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }
    // Listen for incoming connections
    listen(sockfd, kMaxConnections);

    // Accept client connections in a loop
    while (true) {
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        // Create a new thread to handle the client request
        pthread_t thread;
        int result = pthread_create(&thread, NULL, &handle_client_request, &newsockfd);
        if (result != 0) {
            std::cerr << "Error creating thread: " << result << std::endl;
            close(newsockfd);
            continue;
        }

    }
    close(sockfd);
    return 0;
}