#ifndef USER_H 
#define USER_H

#include<iostream>
#include<libpq-fe.h>
#include<string>

namespace USR {
    class User {
        private:
            int id_user;
            std::string CI;
            std::string user_name;
            std::string password;
            int user_type;

        public:
            User(const int id_user, std::string CI, std::string user_name, std::string password, int user_type);
            ~User();

            int get_id_user();
            std::string get_CI();
            std::string get_user_name();
            std::string get_password();
    };
}

#endif // USER_H