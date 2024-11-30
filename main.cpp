#include<iostream>
#include<libpq-fe.h>

#include "gc-functions/gc.h"
#include "menu-users/menu.h"
#include "menu-users/usr.h"

int main (){

    GC::DBgc *gc_db = new GC::DBgc(GC::connDB); // aqui se realiza la conexion a la base de dato y otras operaciones inciales

    while (true){ // en este bucle inicia la aplicacion
        if(gc_db->searchAdmin()){
            std::string user, pass, salir;
            // ---------------------- sistema de logueo ------------------------------------
            while (true) {
                // segun el usuario digitado y su tipo de usario se desplegara el menu correspondiente
                std::cout << "Digite su usuario -> "; std::getline(std::cin, user);
                std::cout << "Digite su contrasena ->"; std::getline(std::cin, pass);
                if (gc_db->searchUser(user, pass)){ // se verifica si el usuario existe
                
                    std::cout << "El usuario se ha encontrado con excito" << std::endl; 
                    PGresult* user_get = gc_db->getUserType_BD(user, pass); // obtenemos los dato del tipo de usuario

                    // obtenemos los datos correspondientes al usuario
                    std::string id_user, CI, user_name, password, user_type;  
                    id_user = PQgetvalue(user_get, 0, 0);
                    CI = PQgetvalue(user_get, 0, 1);
                    user_name = PQgetvalue(user_get, 0, 2);
                    password = PQgetvalue(user_get, 0, 3);
                    user_type = PQgetvalue(user_get, 0, 4);

                    std::cout << id_user << std::endl;

                    USR::User *user;
                    user = new USR::User(id_user, CI, user_name, password, user_type);

                    switch (stoi(user_type)) {
                        case 1:
                            menu_admin(user, gc_db);
                            break;
                        case 2:
                            menu_profesor(user, gc_db);
                            break;
                        case 3:
                            menu_student(user, gc_db);
                            break;

                        default:
                            std::cout<< "El usuario es otra cosa" << std::endl;
                            break;
                    }

                    std::cout << "Digite s si quiere salir de la aplicacion -> "; std::getline(std::cin, salir);

                    if (salir == "s"){
                        break;
                    }
                }
            }
            // -------------------------------------------------------------------------------------------------------------------
        } else {
            std::cout << "Es necesario agregar al menos un usuario de tipo admin" << std::endl;
            gc_db->addUser("1");
            std::cout << "Es necesario agregar al menos una facultad" << std::endl;
            gc_db->addFaculty();
            std::cout << "Es necesario agregar al menos un departamento" << std::endl;
            gc_db->addDeparment();
            std::cout << "Es necesario agregar al menos un profesor" << std::endl;
            gc_db->addProfessor("2");
            std::cout << "Es necesario agregar al menos una carrera" << std::endl;
            gc_db->addCareer();
            std::cout << "Es necesario agregar al menos una asignatura" << std::endl;
            gc_db->addSubject();
            std::cout << "Es necesario agregar al menos un estudiante" << std::endl;
            gc_db->addStudent("3");
        }
    }

    gc_db->~DBgc();

    system("pause");

    return 0;
}