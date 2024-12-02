#include "gc.h"

namespace GC {

    void DBgc::deleteStudent() {
        std::string CI_identity;

        std::cout << "Ingrese el CI del estudiante a eliminar -> " << std::endl; 
        std::getline(std::cin, CI_identity);

        // Verificar si el estudiante existe
        PGresult *res = PQexecParams(conn_gc,
            "SELECT * FROM users WHERE CI_identity = $1;",
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

        // Eliminar datos relacionados en la tabla evaluations
        res = PQexecParams(conn_gc,
            "DELETE FROM evaluations WHERE id_student = (SELECT id_student FROM view_info_pers_student WHERE CI_identity = $1);",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in evaluations: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);

        // Eliminar datos relacionados en la tabla classes
        res = PQexecParams(conn_gc,
            "DELETE FROM classes WHERE id_student = (SELECT id_student FROM view_info_pers_student WHERE CI_identity = $1);",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in classes: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);


        // Eliminar datos relacionados en la tabla personal_dates
        res = PQexecParams(conn_gc,
            "DELETE FROM personal_dates WHERE CI_identity = $1",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in personal_dates: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);

        // Eliminar datos relacionados en la tabla users_images
        res = PQexecParams(conn_gc,
            "DELETE FROM users_images WHERE id_user = (SELECT id_user FROM users WHERE CI_identity = $1)",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in users_images: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);

        // Eliminar datos del estudiante en la tabla students
        res = PQexecParams(conn_gc,
            "DELETE FROM students WHERE id_user = (SELECT id_user FROM users WHERE CI_identity = $1);",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in students: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);

        // Eliminar datos del usuario en la tabla users
        res = PQexecParams(conn_gc,
            "DELETE FROM users WHERE CI_identity = $1;",
            1,
            NULL,
            (const char * const *)&CI_identity,
            NULL,
            NULL,
            0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "DELETE command failed in users: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        PQclear(res);
        std::cout << "Estudiante eliminado correctamente." << std::endl;
    }
}