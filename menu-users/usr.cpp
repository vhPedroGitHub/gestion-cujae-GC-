#include "usr.h"

namespace USR{
    User::User(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type,
    std::string _person_n, std::string _last_name_1, std::string _last_name_2){
        id_user = _id_user; CI = _CI; user_name =_user_name; password = _password; user_type = _user_type;
        person_n = _person_n; last_name_1 = _last_name_1; last_name_2 = last_name_2;
    }

    User::~User(){}

    int User::get_id_user(){return id_user;}
    std::string User::get_CI(){return CI;}
    std::string User::get_user_name(){return user_name;}
    std::string User::get_password(){return password;}
    std::string User::get_person_n(){return person_n;}
    std::string User::get_last_name_1(){return last_name_1;}
    std::string User::get_last_name_2(){return last_name_2;}

    Profesor::Profesor(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type,
    std::string _person_n, std::string _last_name_1, std::string _last_name_2,
    int _id_profesor, int _id_deparment, std::string _category) : User(_id_user, _CI, _user_name, _password, _user_type, _person_n, _last_name_1, _last_name_2){
        id_profesor = _id_profesor;
        id_deparment = _id_deparment;
        category = _category;
    }

    Profesor::~Profesor(){}

    Student::Student(int _id_user, std::string _CI, std::string _user_name, std::string _password, int _user_type,
    std::string _person_n, std::string _last_name_1, std::string _last_name_2,
    int _id_student, int _id_faculty, int _id_career, int _group) : User(_id_user, _CI, _user_name, _password, _user_type, _person_n, _last_name_1, _last_name_2){
        id_student = _id_student;
        id_faculty = _id_faculty;
        id_career = _id_career;
        group = _group;
    }

    Student::~Student(){}
}