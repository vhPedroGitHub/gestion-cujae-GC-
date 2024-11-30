#ifndef USER_H 
#define USER_H

#include<iostream>
#include<libpq-fe.h>
#include<string>

namespace USR {
    class User {
        private:
            std::string id_user;
            std::string CI;
            std::string user_names;
            std::string password;
            std::string user_type;

        public:
            User(std::string id_user, std::string CI, std::string user_name, std::string password, std::string user_type);
            ~User();

            std::string get_id_user();
            std::string get_CI();
            std::string get_user_name();
            std::string get_password();
    };
}

#endif // USER_H