#include "gc.h"

namespace GC {
    PGresult* DBgc::getUserType_BD(const std::string username, const std::string password) {
        // Consulta SQL para verificar usuario y contraseña
        const char *paramValues[2] = { username.c_str(), password.c_str() };

        PGresult *res = PQexecParams(conn_gc,
                                     "SELECT id_user, u.CI, user_name, password_user, user_type, person_n, last_name_1, last_name_2 "
                                     "FROM users u "
                                     "INNER JOIN personal_dates pd ON pd.CI = u.CI "
                                     "WHERE user_name = $1 AND password_user = $2",
                                     2,       // Número de parámetros
                                     NULL,    // Tipos de parámetros (NULL para usar tipos predeterminados)
                                     paramValues,
                                     NULL,    // Longitudes de parámetros (NULL para texto)
                                     NULL,    // Formatos de parámetros (NULL para texto)
                                     0);      // Formato de resultados (0 para texto)

        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "SELECT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return nullptr;
        }

        return res;
    }
}
