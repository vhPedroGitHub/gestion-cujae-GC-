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

    Profesor::Profesor(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type,
    int _id_profesor, int _id_deparment, std::string _category) : User(_id_user, _CI, _user_name, _password, _user_type){
        id_profesor = _id_profesor;
        id_deparment = _id_deparment;
        category = _category;
    }

    Profesor::~Profesor(){}

    Student::Student(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type,
    int _id_student, int _id_faculty, int _id_career, int _group) : User(_id_user, _CI, _user_name, _password, _user_type){
        id_student = _id_student;
        id_faculty = _id_faculty;
        id_career = _id_career;
        group = _group;
    }

    Student::~Student(){}
}