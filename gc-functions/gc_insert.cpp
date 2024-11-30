#include "gc.h"
#include <vector>
#include <limits>

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
    std::string selectElement( std::vector<ConsultInd> elements) {
        int selection = -1;

        while (true) {
            std::cout << "Seleccione un elemento del siguiente listado:\n";
            for (size_t i = 0; i < elements.size(); ++i) {
                std::cout << i + 1 << ". " << elements[i].getValue() << "\n";
            }
            
            std::cout << "Ingrese el número del elemento seleccionado: ";
            std::cin >> selection;

            if (selection > 0 && selection <= elements.size()) {
                return elements[selection-1].getIndice();
            } else {
                std::cout << "Selección inválida. Por favor, intente nuevamente.\n";
            }
        }
    }

    void DBgc::addUser(std::string user_type) {
        std::string user_name, password_user;
        const char *paramValues[4];

        std::cout << "Agregue el nombre del usuario admin -> " << std::endl; std::getline(std::cin, user_name);
        std::cout << "Agregue la contrasena -> " << std::endl; std::getline(std::cin, password_user);

        // Iniciar la transacción
        PGresult *res = PQexec(conn_gc, "BEGIN");

        PQclear(res);

        paramValues[0] = user_name.c_str();
        paramValues[1] = password_user.c_str();
        paramValues[2] = user_type.c_str();

        //const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
        res = PQexecParams(conn_gc,
                        "INSERT INTO users (user_name, password_user, user_type) VALUES ($1, $2, $3)",
                        3,
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

        std::cout << "Todo termino correctamente" << std::endl;
        PQclear(res);
    }

    void DBgc::addProfessor(std::string user_type){
        std::string CI_identity, user_name, password_user, name, last_name_1, last_name_2;

        std::cout << "Agregue el CI_identity -> " << std::endl; std::getline(std::cin, CI_identity);
        std::cout << "Agregue el nombre de usuario -> " << std::endl; std::getline(std::cin, user_name);
        std::cout << "Agregue la contrasena -> " << std::endl; std::getline(std::cin, password_user);

        // Iniciar la transacción
        PGresult *res = PQexec(conn_gc, "BEGIN");

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "BEGIN command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
            return;
        }

        const char *paramValues_1[4];
        paramValues_1[0] = CI_identity.c_str();
        paramValues_1[1] = user_name.c_str();
        paramValues_1[2] = password_user.c_str();
        paramValues_1[3] = user_type.c_str();

        const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
        res = PQexecParams(conn_gc,
                        "INSERT INTO users (CI_identity, user_name, password_user, user_type) VALUES ($1, $2, $3, $4)",
                        4,
                        paramsTypes,
                        paramValues_1,
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

        const char *paramValues_2[4];
        paramValues_2[0] = CI_identity.c_str();
        paramValues_2[1] = name.c_str();
        paramValues_2[2] = last_name_1.c_str();
        paramValues_2[3] = last_name_2.c_str();

        res = PQexecParams(conn_gc,
                        "INSERT INTO personal_dates (CI_identity, person_n, last_name_1, last_name_2) VALUES ($1, $2, $3, $4)",
                        4,
                        NULL,
                        paramValues_2,
                        NULL,
                        NULL,
                        0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "INSERT command failed: " << PQerrorMessage(conn_gc) << std::endl;
            PQexec(conn_gc, "ROLLBACK");
            PQclear(res);
            return;
        }

        // agregando los datos particulares del profesor
        
        std::vector<ConsultInd> deparments = DBgc::getInfos("deparments", "id_deparment", "n_deparment");

        std::string deparment_select = selectElement(deparments);
        std::cout << "seleccionado el departameto" << std::endl;
        int user_id = getLastUserId(conn_gc);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::string category;

        std::cout << "Digite la categoria del profesor -> "; std::getline(std::cin, category);
    
        const char *paramValues_profesor[3] = { deparment_select.c_str(), std::to_string(user_id).c_str(), category.c_str() };
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
        std::string CI_identity, user_name, password_user, name, last_name_1, last_name_2;

        std::cout << "Agregue el CI_identity -> " << std::endl; std::getline(std::cin, CI_identity);
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

        const Oid paramsTypes[4] = {1043, 1043, 1043, 23};
        const char *paramValues_1[4];
        paramValues_1[0] = CI_identity.c_str();
        paramValues_1[1] = user_name.c_str();
        paramValues_1[2] = password_user.c_str();
        paramValues_1[3] = user_type.c_str();

        res = PQexecParams(conn_gc,
                        "INSERT INTO users (CI_identity, user_name, password_user, user_type) VALUES ($1, $2, $3, $4)",
                        4,
                        paramsTypes,
                        paramValues_1,
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

        const char * paramValues_2[4];
        paramValues_2[0] = CI_identity.c_str();
        paramValues_2[1] = name.c_str();
        paramValues_2[2] = last_name_1.c_str();
        paramValues_2[3] = last_name_2.c_str();

        res = PQexecParams(conn_gc,
                        "INSERT INTO personal_dates (CI_identity, person_n, last_name_1, last_name_2) VALUES ($1, $2, $3, $4)",
                        4,
                        NULL,
                        paramValues_2,
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

        // agregando los datos particulares del alumno
        int user_id = getLastUserId(conn_gc);

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::string group;

        std::cout << "Digite el grupo del alumno -> "; std::getline(std::cin, group);
    
        const char *paramValues_profesor[3] = { std::to_string(user_id).c_str(), NULL, group.c_str() };
        std::string query = "INSERT INTO students (id_user, id_career_year, group_student) VALUES ($1, $2, $3)"; 
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

        // Insertar en la tabla careers_years
        for (int age = 1; age <= duration; ++age) {
            std::string insert_age_query = "INSERT INTO careers_years (id_career, year) VALUES (" +
                                        std::to_string(career_id) + ", " + std::to_string(age) + ")";
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
        // Consulta SQL para insertar un nuevo registro en la tabla subjects
        const char* query = "INSERT INTO subjects (id_profesor, n_subject) VALUES ($1, $2)";
        
        std::string n_subject;

        std::cout << "Diga el nombre de la asignatura"; std::getline(std::cin, n_subject);

        // Parámetros para la consulta
        const char* paramValues[2];
        paramValues[0] = NULL;
        paramValues[1] = n_subject.c_str();

        // Ejecutar la consulta
        PGresult *res = PQexecParams(conn_gc,
                                    query,
                                    2, 
                                    NULL, 
                                    paramValues,
                                    NULL,
                                    NULL, 
                                    0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error inserting subject: " << PQerrorMessage(conn_gc) << std::endl;
        } else {
            std::cout << "Subject inserted successfully." << std::endl;
        }

        PQclear(res); // Liberar el resultado
    }

    void DBgc::addImage(){
        // en este metodo se le agregara una imagen a un alumno para que pueda ser identificado por una foto
        // Variables para almacenar los datos del formulario
        std::string name_img, directory_img = "../sources/face_imgs/";
        std::string id_user;

        // Simulando la entrada del formulario
        std::cout << "Ingrese el nombre de la imagen: ";
        std::getline(std::cin, name_img);
        directory_img = directory_img + name_img;
        std::cout << "Ingrese el ID del usuario: ";
        std::getline(std::cin, id_user);

        // Consulta SQL para insertar datos en la tabla users_images
        std::string sql = "INSERT INTO users_images (directory_img, id_user) VALUES ($1, $2);";

        const char *paramValues[2] = {directory_img.c_str(), id_user.c_str()};

        // Preparar la consulta
        PGresult *res = PQexecParams(conn_gc, sql.c_str(),
                                    2,       // Número de parámetros
                                    NULL,    // No se utilizan parámetros de tipo
                                    paramValues,
                                    NULL, NULL,  // Sin parámetros adicionales
                                    0);          // Sin formato

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error al insertar datos: " << PQerrorMessage(conn_gc) << std::endl;
        } else {
            std::cout << "Datos insertados correctamente." << std::endl;
        }

        // Limpiar resultados y cerrar conexión
        PQclear(res);
    }

    void DBgc::addClass(const std::string id_subject, const std::string id_student, 
    const std::string cantidad_turnos, const std::string date_class, const std::string assis) {
        PGconn *conn = PQconnectdb(connDB);

        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            return;
        }

        // Preparar la consulta SQL
        const char *sql = "INSERT INTO classes (id_subject, id_student, cantidad_turnos, date_class, assis) VALUES ($1, $2, $3, $4, $5);";
        
        // Crear un objeto para almacenar el resultado
        PGresult *res;

        const char *paramValues[5]={id_subject.c_str(), id_student.c_str(), cantidad_turnos.c_str(), date_class.c_str(), assis.c_str()};
        // Usar PQexecParams para ejecutar la consulta con parámetros
        res = PQexecParams(conn,
                        sql,
                        5, 
                        NULL, 
                        paramValues,
                        NULL,
                        NULL,
                        0); // No se necesita formato

        // Verificar si la consulta fue exitosa
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error al insertar clase: " << PQerrorMessage(conn) << std::endl;
        }

        // Liberar el resultado
        PQclear(res);
    }
}

