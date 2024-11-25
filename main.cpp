#include<iostream>
#include<libpq-fe.h>

#include "gc-functions/gc.h"
#include "menu-users/menu.h"
#include "menu-users/usr.h"

int main (){

    GC::DBgc *gc_db = new GC::DBgc(GC::connDB); // aqui se realiza la conexion a la base de dato y otras operaciones inciales

    while (true){ // en este bucle inicia la aplicacion
        if(gc_db->searchAdmin()){
            std::string user, pass;
            // ---------------------- sistema de logueo ------------------------------------
            while (true) {
                // segun el usuario digitado y su tipo de usario se desplegara el menu correspondiente
                std::cout << "Digite su usuario -> "; std::getline(std::cin, user);
                std::cout << "Digite su contrasena ->"; std::getline(std::cin, pass);
                if (gc_db->searchUser(user, pass)){ // se verifica si el usuario exciste
                    std::cout << "El usuario se ha encontrado con excito" << std::endl; 
                    PGresult* user_get = gc_db->getUserType_BD(user, pass); // obtenemos los dato del tipo de usuario

                    // obtenemos los datos correspondientes al usuario
                    std::string id_user, CI, user_name, password, user_type, person_n, last_name_1, last_name_2;  
                    id_user = PQgetvalue(user_get, 0, 0);
                    CI = PQgetvalue(user_get, 0, 1);
                    user_name = PQgetvalue(user_get, 0, 2);
                    password = PQgetvalue(user_get, 0, 3);
                    user_type = PQgetvalue(user_get, 0, 4);
                    person_n = PQgetvalue(user_get, 0, 5);
                    last_name_1 = PQgetvalue(user_get, 0, 6);
                    last_name_2 = PQgetvalue(user_get, 0, 7);

                    USR::User *admin;

                    switch (stoi(user_type)) {
                        case 1:
                            admin = new USR::User(stoi(id_user), CI, user_name, password, stoi(user_type), person_n, last_name_1, last_name_2);
                            menu_admin(admin, gc_db);
                            break;
                        case 2:
                            std::cout<< "El usuario es un profesor" << std::endl;
                            break;
                        case 3:
                            std::cout<< "El usuario es un estudiante" << std::endl;
                            break;

                        default:
                            std::cout<< "El usuario es otra cosa" << std::endl;
                            break;
                    }

                }
            }
            // -------------------------------------------------------------------------------------------------------------------
        } else {
            std::cout << "Debe agregar un admin para poder realizar otras operaciones" << std::endl;
            gc_db->addUser("1");
        }
    }

    gc_db->~DBgc();

    system("pause");

    return 0;
}