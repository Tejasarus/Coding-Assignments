#ifndef __ACC_HPP__
#define __ACC_HPP__
#include <iostream>
class Account
{
    public:

        Account(){};

        Account(std::string account_n, std::string account_pass)
        {
            account_name = account_n;
            account_password = account_pass;
        };

        std::string get_username(){ return account_name;};
        std::string get_password(){ return account_password;};


    private:

        std::string account_name;
        std::string account_password;
    
};


#endif
