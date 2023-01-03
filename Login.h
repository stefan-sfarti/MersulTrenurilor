//
// Created by stefan on 02.01.2023.
//

#ifndef TRIAL_LOGIN_H
#define TRIAL_LOGIN_H
#include <iostream>

class Login {
public:
    bool CheckUsername(std::string username);
    bool CheckPassword(std::string password);
    bool RegisterAccount(std::string username, std::string password);
};


#endif //TRIAL_LOGIN_H
