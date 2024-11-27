#include "gc.h"
#include <vector>
#include <limits>

int selectElement(const std::vector<std::string>& elements) {
    int selection = -1;

    while (true) {
        std::cout << "Seleccione un elemento del siguiente listado:\n";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << i + 1 << ". " << elements[i] << "\n";
        }
        
        std::cout << "Ingrese el número del elemento seleccionado: ";
        std::cin >> selection;

        if (selection > 0 && selection <= elements.size()) {
            return selection;
        } else {
            std::cout << "Selección inválida. Por favor, intente nuevamente.\n";
        }
    }
}

int getDeparmentId(PGconn *conn, const std::string departmentName) {
    const char *paramValues[1] = { departmentName.c_str() }; 
    const char *query = "SELECT id_deparment FROM deparments WHERE n_deparment = $1"; 
    Oid type_param[1] = { 25 };
    PGresult *res = PQexecParams(conn, query, 1, type_param, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Error retrieving department ID: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    }

    if (PQntuples(res) == 0) {
        std::cerr << "Department not found.\n";
        PQclear(res);
        return -1; // Indicando que no se encontró el departamento
    }

    int departmentId = std::stoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return departmentId;
}

int getLastUserId(PGconn *conn) {
    const char *query = "SELECT MAX(id_user) FROM users";
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Error retrieving last user ID: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    }

    int lastUserId = -1;  // Valor por defecto en caso de que no haya usuarios
    if (PQntuples(res) > 0 && PQgetvalue(res, 0, 0) != nullptr) {
        lastUserId = std::stoi(PQgetvalue(res, 0, 0));
    }

    PQclear(res);
    return lastUserId;
}

namespace GC {
    void DBgc::addUser(std::string user_type) {
        std::string CI, user_name, password_user, name, last_name_1, last_name_2;
        const char *paramValues[4];

        std::cout << "Agregue el CI -> " << std::endl; std::getline(std::cin, CI);
        std::cout << "Agregue el nombre de usuario -> " << std::endl; std::getline(std::cin, user_name);
        std::cout << "Agregue la contrasena -> " << std::endl; std::getline(std::cin, password_user);

        // Iniciar la transacción
        PGresult *res = PQexec(conn_gc, "BEGIN");

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "BEGIN command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }
        PQclear(res);

        paramValues[0] = CI.c_str();
        paramValues[1] = user_name.c_str();
        paramValues[2] = password_user.c_str();
        paramValues[3] = user_type.c_str();

        const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
        res = PQexecParams(conn_gc,
                        "INSERT INTO users (CI, user_name, password_user, user_type) VALUES ($1, $2, $3, $4)",
                        4,
                        paramsTypes,
                        paramValues,
                        NULL,
                        NULL,
                        0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
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
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        // Commit la transacción si todo va bien
        res = PQexec(conn_gc, "COMMIT");

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "COMMIT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        std::cout << "Todo termino correctamente" << std::endl;
        PQclear(res);
    }

    void DBgc::addProfessor(std::string user_type){
        std::string CI, user_name, password_user, name, last_name_1, last_name_2;
        const char *paramValues[4];

        std::cout << "Agregue el CI -> " << std::endl; std::getline(std::cin, CI);
        std::cout << "Agregue el nombre de usuario -> " << std::endl; std::getline(std::cin, user_name);
        std::cout << "Agregue la contrasena -> " << std::endl; std::getline(std::cin, password_user);

        // Iniciar la transacción
        PGresult *res = PQexec(conn_gc, "BEGIN");

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "BEGIN command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }
        PQclear(res);

        paramValues[0] = CI.c_str();
        paramValues[1] = user_name.c_str();
        paramValues[2] = password_user.c_str();
        paramValues[3] = user_type.c_str();

        const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
        res = PQexecParams(conn_gc,
                        "INSERT INTO users (CI, user_name, password_user, user_type) VALUES ($1, $2, $3, $4)",
                        4,
                        paramsTypes,
                        paramValues,
                        NULL,
                        NULL,
                        0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
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
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        PQclear(res);

        res = PQexec(conn_gc, "SELECT n_deparment FROM deparments");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error retrieving deparments: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        // agregando los datos particulares del profesor
        std::vector<std::string> deparments;
        int nDeparments = PQntuples(res);
        for (int i = 0; i < nDeparments; ++i) {
            deparments.push_back(PQgetvalue(res, i, 0));
        }

        PQclear(res);

        int deparment_select = selectElement(deparments);

        int deparment_id = getDeparmentId(conn_gc, deparments[deparment_select-1]);
        std::cout << "seleccionado el departameto" << std::endl;
        int user_id = getLastUserId(conn_gc);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::string category;

        std::cout << "Digite la categoria del profesor -> "; std::getline(std::cin, category);
    
        const char *paramValues_profesor[3] = { std::to_string(deparment_id).c_str(), std::to_string(user_id).c_str(), category.c_str() };
        std::string query = "INSERT INTO profesors (id_deparment, id_user, category) VALUES ($1, $2, $3)"; 
        // Ejecutar la consulta 
        res = PQexecParams(conn_gc, query.c_str(), 3, NULL, paramValues_profesor, NULL, NULL, 0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        PQclear(res);

        res = PQexec(conn_gc, "COMMIT");

        // Commit la transacción si todo va bien
        std::cout << "Todo termino correctamente" << std::endl;
        PQclear(res);
    }

    void DBgc::addStudent(std::string user_type){
        
    }

    void DBgc::addFaculty(){

        std::string n_faculty;

        std::cout << "Introduce el nombre de la facultad -> "; std::getline(std::cin, n_faculty);

        std::string query = "INSERT INTO faculties (n_faculty) VALUES ('" + n_faculty + "');";

        PGresult *res = PQexec(conn_gc, query.c_str());

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error al insertar la facultad: " << PQerrorMessage(conn_gc) << std::endl;
        } else {
            std::cout << "Facultad insertada correctamente." << std::endl;
        }

        PQclear(res);
    }

    void DBgc::addDeparment(){

        std::string n_deparment;

        std::cout << "Introduce el nombre del departamento -> "; std::getline(std::cin, n_deparment);

        std::string query = "INSERT INTO deparments (n_deparment) VALUES ('" + n_deparment + "');";

        PGresult *res = PQexec(conn_gc, query.c_str());

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error al insertar el departamento: " << PQerrorMessage(conn_gc) << std::endl;
        } else {
            std::cout << "Departamento insertado correctamente." << std::endl;
        }

        PQclear(res);
    }

    void DBgc::addCareer(){
        PGresult *res;

        // Obtener todas las facultades
        res = PQexec(conn_gc, "SELECT id_faculty, n_faculty FROM faculties ORDER BY id_faculty");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error retrieving faculties: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        int nFaculties = PQntuples(res);
        std::cout << "Facultades disponibles:\n";
        for (int i = 0; i < nFaculties; ++i) {
            std::cout << PQgetvalue(res, i, 0) << ". " << PQgetvalue(res, i, 1) << "\n";
        }
        PQclear(res);

        // Solicitar datos del usuario
        std::string career_name;
        int faculty_id, duration;
        std::cout << "Ingrese el nombre de la carrera: ";
        std::cin >> career_name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::cout << "Ingrese el ID de la facultad: ";
        std::cin >> faculty_id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::cout << "Ingrese la duración (años): ";
        std::cin >> duration;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        // Verificar si la facultad existe
        std::string faculty_check_query = "SELECT COUNT(*) FROM faculties WHERE id_faculty = " + std::to_string(faculty_id);
        res = PQexec(conn_gc, faculty_check_query.c_str());
        if (PQresultStatus(res) != PGRES_TUPLES_OK || PQgetvalue(res, 0, 0)[0] == '0') {
            std::cerr << "Faculty ID not found or error: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }
        PQclear(res);

        // Insertar en la tabla careers
        std::string insert_career_query = "INSERT INTO careers (id_faculty, n_career, duration) VALUES (" +
                                        std::to_string(faculty_id) + ", '" + career_name + "', " + std::to_string(duration) + ") RETURNING id_career";
        res = PQexec(conn_gc, insert_career_query.c_str());
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error inserting career: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }
        int career_id = std::stoi(PQgetvalue(res, 0, 0));
        PQclear(res);

        // Insertar en la tabla careers_age
        for (int age = 1; age <= duration; ++age) {
            std::string insert_age_query = "INSERT INTO careers_age (age, id_career) VALUES (" +
                                        std::to_string(age) + ", " + std::to_string(career_id) + ")";
            res = PQexec(conn_gc, insert_age_query.c_str());
            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << "Error inserting career age: " << PQerrorMessage(conn_gc) << std::endl;
                PQclear(res);
            }
            PQclear(res);
        }

        std::cout << "Carrera agregada.\n";
    }

    void DBgc::addSubject(){

    }

}

