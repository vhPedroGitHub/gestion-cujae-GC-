#include "gc.h"

bool GC::DBgc::searchEmptyElements(GC::DBgc *gc_db) {
    PGconn *conn_gc = PQconnectdb(connDB);

    if(PQstatus(conn_gc) == CONNECTION_OK){
        std::cout << "La conexion se ha realizado con exito" << std::endl;
    } else{
        std::cout << "No se ha podido cargar la base de datos" << PQerrorMessage(conn_gc) << std::endl;
        system("pause");
        PQfinish(conn_gc);
    }

    const char *query_1 = "SELECT * FROM users WHERE user_type = 1";
    const char *query_2 = "SELECT * FROM faculties";
    const char *query_3 = "SELECT * FROM deparments";
    const char *query_4 = "SELECT * FROM profesors";
    const char *query_5 = "SELECT * FROM careers";
    const char *query_6 = "SELECT * FROM subjects";
    const char *query_7 = "SELECT * FROM students";

    PGresult *res_1 = PQexec(conn_gc, query_1);
    PGresult *res_2 = PQexec(conn_gc, query_2);
    PGresult *res_3 = PQexec(conn_gc, query_3);
    PGresult *res_4 = PQexec(conn_gc, query_4);
    PGresult *res_5 = PQexec(conn_gc, query_5);
    PGresult *res_6 = PQexec(conn_gc, query_6);
    PGresult *res_7 = PQexec(conn_gc, query_7);

    bool N_1 = PQntuples(res_1) == 0;
    bool N_2 = PQntuples(res_2) == 0;
    bool N_3 = PQntuples(res_3) == 0;
    bool N_4 = PQntuples(res_4) == 0;
    bool N_5 = PQntuples(res_5) == 0;
    bool N_6 = PQntuples(res_6) == 0;
    bool N_7 = PQntuples(res_7) == 0;

    if(N_1){
        std::cout << "Es necesario agregar al menos un usuario de tipo admin" << std::endl;
        gc_db->addUser("1");
    }
    if(N_2){
        std::cout << "Es necesario agregar al menos una facultad" << std::endl;
        gc_db->addFaculty();
    }
    if(N_3){
        std::cout << "Es necesario agregar al menos un departamento" << std::endl;
        gc_db->addDeparment();
    }
    if(N_4){
        std::cout << "Es necesario agregar al menos un profesor" << std::endl;
        gc_db->addProfessor("2");
    }
    if(N_5){    
        std::cout << "Es necesario agregar al menos una carrera" << std::endl;
        gc_db->addCareer();
    }
    if(N_6){
        std::cout << "Es necesario agregar al menos una asignatura" << std::endl;
        gc_db->addSubject();
    }
    if(N_7){
        std::cout << "Es necesario agregar al menos un estudiante" << std::endl;
        gc_db->addStudent("3");
    }

    if(N_1 || N_2 || N_3 || N_4 || N_5 || N_6 || N_7){
        PQclear(res_1);
        PQclear(res_2);
        PQclear(res_3);
        PQclear(res_4);
        PQclear(res_5);
        PQclear(res_6);
        PQclear(res_7);
        return true;
    }

    PQclear(res_1);
    PQclear(res_2);
    PQclear(res_3);
    PQclear(res_4);
    PQclear(res_5);
    PQclear(res_6);
    PQclear(res_7);
    return false;
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
