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
            std::string person_n;
            std::string last_name_1;
            std::string last_name_2;

        public:
            User(const int id_user, std::string CI, std::string user_name, std::string password, int user_type, 
            std::string person_n, std::string last_name_1, std::string last_name_2);
            ~User();

            int get_id_user();
            std::string get_CI();
            std::string get_user_name();
            std::string get_password();
            std::string get_person_n();
            std::string get_last_name_1();
            std::string get_last_name_2();
    };

    class Profesor : public User {
        private:
            int id_profesor;
            int id_deparment;
            std::string category;

        public:
            Profesor(int id_user, std::string CI, std::string user_name, std::string password, int user_type,
            std::string person_n, std::string last_name_1, std::string last_name_2, 
            int id_profesor, int id_deparment, std::string category);
            ~Profesor();
    };

    class Student : public User {
        private:
            int id_student;
            int id_faculty;
            int id_career;
            int group;

        public:
            Student(int id_user, std::string CI, std::string user_name, std::string password, int user_type,
            std::string person_n, std::string last_name_1, std::string last_name_2,
            int id_student, int id_faculty, int id_career, int group);
            ~Student();
    };
}

#endif // USER_H