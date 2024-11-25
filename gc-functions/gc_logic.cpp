#include "gc.h"

bool GC::DBgc::searchAdmin() {
    const char *query = "SELECT * FROM users WHERE user_type = 1 LIMIT 1";
    PGresult *res = PQexec(conn_gc, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQerrorMessage(conn_gc) << std::endl;
        PQclear(res);
        PQfinish(conn_gc);
        return false;
    }

    bool hasAdmin = PQntuples(res) > 0;

    PQclear(res);
    return hasAdmin;
}

bool GC::DBgc::searchUser(const std::string username, const std::string password) {
    // Consulta SQL para verificar usuario y contraseña
    const char *paramValues[2] = { username.c_str(), password.c_str() };

    PGresult *res = PQexecParams(conn_gc,
                                 "SELECT * FROM users WHERE user_name = $1 AND password_user = $2",
                                 2,       // Número de parámetros
                                 NULL,    // Tipos de parámetros (NULL para usar tipos predeterminados)
                                 paramValues,
                                 NULL,    // Longitudes de parámetros (NULL para texto)
                                 NULL,    // Formatos de parámetros (NULL para texto)
                                 0);      // Formato de resultados (0 para texto)

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "SELECT command failed: " << PQerrorMessage(conn_gc) << std::endl;
        PQclear(res);
        return false;
    }

    bool userExists = PQntuples(res) > 0;
    PQclear(res);
    return userExists;
}
