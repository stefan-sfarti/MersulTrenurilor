//
// Created by stefan on 25.12.2022.
//

#ifndef MERSULTRENURILOROOP_LOGIN_H
#define MERSULTRENURILOROOP_LOGIN_H


#include "Register.h"
#include "string"

class Login : Register {
private:
    bool loggedin{false};
    std::string username{"Guest"};
public:
    bool CheckUsername (std::string username);
    bool IsLoggedIn ();
    bool LogIn(std::string username, std::string password);
};


#endif //MERSULTRENURILOROOP_LOGIN_H
