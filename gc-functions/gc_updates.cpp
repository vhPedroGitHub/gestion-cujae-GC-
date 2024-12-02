#include "gc.h"

namespace GC {

    void DBgc::updateStudent(){

       std::string CI_identity, user_name, password_user, name, last_name_1, last_name_2, group;
        std::cout << "Ingrese el CI del estudiante a modificar -> " << std::endl; 
        std::getline(std::cin, CI_identity);

        // Verificar si el estudiante existe
        PGresult *res = PQexecParams(conn_gc,
            "SELECT * FROM users WHERE CI_identity = $1",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
            std::cerr << "Estudiante no encontrado." << std::endl;
            PQclear(res);
            return;
        }
        PQclear(res);

        // Solicitar nuevos datos
        std::cout << "Ingrese el nuevo nombre de usuario -> " << std::endl; 
        std::getline(std::cin, user_name);
        std::cout << "Ingrese la nueva contrasena -> " << std::endl; 
        std::getline(std::cin, password_user);
        
        std::cout << "Ingrese el nuevo nombre -> " << std::endl; 
        std::getline(std::cin, name);
        std::cout << "Ingrese el nuevo primer apellido -> " << std::endl; 
        std::getline(std::cin, last_name_1);
        std::cout << "Ingrese el nuevo segundo apellido -> " << std::endl; 
        std::getline(std::cin, last_name_2);
        
        std::cout << "Digite el nuevo grupo del alumno -> "; 
        std::getline(std::cin, group);

        // Iniciar la transacción
        res = PQexec(conn_gc, "BEGIN");

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "BEGIN command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }
        PQclear(res);

        // Actualizar datos del usuario
        const char *paramValues_user[4] = { user_name.c_str(), password_user.c_str(), CI_identity.c_str(), CI_identity.c_str() };
        
        res = PQexecParams(conn_gc,
            "UPDATE users SET user_name = $1, password_user = $2 WHERE CI_identity = $3",
            3,
            NULL,
            paramValues_user,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "UPDATE command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }
        
        PQclear(res);

        // Actualizar datos personales
        const char *paramValues_personal[4] = { name.c_str(), last_name_1.c_str(), last_name_2.c_str(), CI_identity.c_str() };

        res = PQexecParams(conn_gc,
            "UPDATE personal_dates SET person_n = $1, last_name_1 = $2, last_name_2 = $3 WHERE CI_identity = $4",
            4,
            NULL,
            paramValues_personal,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "UPDATE command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        PQclear(res);

        // Actualizar datos del estudiante
        const char *paramValues_student[3] = { group.c_str(), CI_identity.c_str() };

        res = PQexecParams(conn_gc,
            "UPDATE students SET group_student = $1 WHERE id_user = (SELECT id_user FROM users WHERE CI_identity = $2)",
            2,
            NULL,
            paramValues_student,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "UPDATE command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        PQclear(res);

        // Commit la transacción si todo va bien
        res = PQexec(conn_gc, "COMMIT");
        
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "COMMIT command failed: " << PQerrorMessage(conn_gc) << std::endl;
        return;
    }

    PQclear(res);
    std::cout << "Datos del estudiante actualizados correctamente." << std::endl;
    }

}