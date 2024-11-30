#include "usr.h"

namespace USR{
    User::User(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type){
        id_user = _id_user; CI = _CI; user_name =_user_name; password = _password; user_type = _user_type;
    }

    User::~User(){}

    int User::get_id_user(){return id_user;}
    std::string User::get_CI(){return CI;}
    std::string User::get_user_name(){return user_name;}
    std::string User::get_password(){return password;}
}