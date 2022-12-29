//
// Created by stefan on 25.12.2022.
//
#ifndef MERSULTRENURILOROOP_REGISTER_H
#define MERSULTRENURILOROOP_REGISTER_H


class Register {
public:
    bool CheckUsername(std::string username);
    bool CheckPassword(std::string password);
    bool RegisterAccount(std::string username, std::string password);
};


#endif //MERSULTRENURILOROOP_REGISTER_H
