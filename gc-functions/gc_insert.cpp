#include "gc.h"
#include<iostream>
#include<string>
#include<libpq-fe.h>

void GC::DBgc::addUser() {
    std::string CI, user_name, password_user, user_type, name, last_name_1, last_name_2;
    const char *paramValues[4];

    std::cout << "Agregue el CI -> " << std::endl; std::getline(std::cin, CI);
    std::cout << "Agregue el nombre de usuario -> " << std::endl; std::getline(std::cin, user_name);
    std::cout << "Agregue la contrasena -> " << std::endl; std::getline(std::cin, password_user);
    std::cout << "Agregue el tipo de usuario -> " << std::endl; std::getline(std::cin, user_type);

    paramValues[0] = CI.c_str();
    paramValues[1] = user_name.c_str();
    paramValues[2] = password_user.c_str();
    paramValues[3] = user_type.c_str();

    const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
    PGresult *res = PQexecParams(conn_gc,
                                 "INSERT INTO users (CI, user_name, password_user, user_type) VALUES ($1, $2, $3, $4)",
                                 4,       
                                 paramsTypes,    
                                 paramValues,
                                 NULL,    
                                 NULL,    
                                 0);    

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
    }

    PQclear(res);

    std::cout << "Agregue el nombre -> " << std::endl; std::getline(std::cin, name);
    std::cout << "Agregue el primer apellido -> " << std::endl; std::getline(std::cin, last_name_1);
    std::cout << "Agregue el segundo apellido -> " << std::endl; std::getline(std::cin, last_name_2);

    paramValues[0] = CI.c_str();
    paramValues[1] = name.c_str();
    paramValues[2] = last_name_1.c_str();
    paramValues[3] = last_name_2.c_str();

    res = PQexecParams(conn_gc,
                                 "INSERT INTO personal_dates (CI, person_n, last_name_1, last_name_2) VALUES ($1, $2, $3, $4)",
                                 4,       
                                 NULL,    
                                 paramValues,
                                 NULL,    
                                 NULL,    
                                 0);    

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
    } else {
        std::cout << "Usuario admin agregado exitosamente." << std::endl;
    }

    PQclear(res);
}
