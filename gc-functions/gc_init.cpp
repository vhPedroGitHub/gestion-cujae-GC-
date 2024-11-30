#include "gc.h"
#include "menu-users/menu.h"

namespace GC {
    const char* connDBG = "user=postgres password=12345678 port=5432 host=localhost";
    const char* connDB = "user=postgres password=12345678 port=5432 dbname=gc host=localhost"; 

    DBgc::DBgc(const char *conninfo){ 
        // en el constructor se intenta siempre acceder a la base de datos hasta que se logra
        while (true) {
            // intentamos acceder a la base de datos
            conn_gc = PQconnectdb(conninfo);

            // comprobamos si se realizo la conexion a la base de dato excitosamente
            if(PQstatus(conn_gc) == CONNECTION_OK){
                std::cout << "La conexion se ha realizado con exito" << std::endl;
                break;
            } else{
                std::cout << "No se ha podido cargar la base de datos" << PQerrorMessage(conn_gc) << std::endl;
                system("pause");
                PQfinish(conn_gc);
                DBgc::create_db_gc(); // con esta funcion se crea la base de datos gc si no esta creada
                DBgc::create_tables_db(); // crean las tablas en la base de datos

            }

            system("pause");
        }
    }

    DBgc::~DBgc(){
        PQfinish(conn_gc);
    }

    void DBgc::create_db_gc(){
        PGconn *conn = PQconnectdb(connDBG);

        if(PQstatus(conn) == CONNECTION_OK){
            std::cout << "La conexion se ha realizado con exito" << std::endl;
        } else{
            std::cout << "No se ha podido cargar la base de datos" << PQerrorMessage(conn) << std::endl;
            system("pause");
            PQfinish(conn);
        }

        // Create de database gc
        const char *create_db_query = "CREATE DATABASE gc";

        // execute the command
        PGresult *res = PQexec(conn, create_db_query);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Error al crear la base de datos: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            PQfinish(conn);
        }

        std::cout << "Base de datos 'gc' creada exitosamente." << std::endl;

        PQclear(res);
        PQfinish(conn);
    }

    void DBgc::create_tables_db(){
        const std::string sql = R"(
            CREATE TABLE students (
            id_student SERIAL PRIMARY KEY,
            id_user INTEGER NOT NULL,
            id_career_year INTEGER,
            group_student INTEGER NOT NULL
            );

            CREATE TABLE profesors (
            id_profesor SERIAL PRIMARY KEY,
            id_deparment INTEGER NOT NULL,
            id_user INTEGER NOT NULL,
            category VARCHAR(50)
            );

            CREATE TABLE subjects (
            id_subject SERIAL PRIMARY KEY,
            id_profesor INTEGER,
            n_subject TEXT
            );

            CREATE TABLE faculties (
            id_faculty SERIAL PRIMARY KEY,
            n_faculty TEXT UNIQUE NOT NULL
            );

            CREATE TABLE careers (
            id_career SERIAL PRIMARY KEY,
            id_faculty INTEGER,
            n_career VARCHAR(50) NOT NULL,
            duration INTEGER NOT NULL
            );

            CREATE TABLE careers_years (
            id_career_year SERIAL PRIMARY KEY,
            id_career INTEGER,
            year INTEGER NOT NULL
            );

            CREATE TABLE careers_subjects (
            id_career_subject SERIAL PRIMARY KEY,
            id_subject INTEGER,
            id_career_year INTEGER
            );

            CREATE TABLE evaluations (
            id_evaluation SERIAL PRIMARY KEY,
            id_student INTEGER,
            id_subject INTEGER,
            calification INTEGER,
            evaluation_type VARCHAR(10),
            date_eval DATE
            );

            CREATE TABLE deparments (
            id_deparment SERIAL PRIMARY KEY,
            n_deparment TEXT UNIQUE
            );

            CREATE TABLE classes (
            id_classe SERIAL PRIMARY KEY,
            id_subject INTEGER,
            id_student INTEGER,
            cantidad_turnos INTEGER,
            date_class DATE,
            assis BOOLEAN
            );

            CREATE TABLE users (
            id_user SERIAL PRIMARY KEY,
            CI_identity VARCHAR(11) UNIQUE,
            user_name VARCHAR(15) NOT NULL,
            password_user VARCHAR(60) NOT NULL,
            user_type INTEGER NOT NULL
            );

            CREATE TABLE personal_dates (
            CI_identity VARCHAR(11) PRIMARY KEY,
            person_n VARCHAR(20) NOT NULL,
            last_name_1 VARCHAR(20) NOT NULL,
            last_name_2 VARCHAR(20) NOT NULL
            );

            CREATE TABLE users_images (
            id_user_image SERIAL PRIMARY KEY,
            directory_img TEXT NOT NULL,
            id_user INTEGER NOT NULL
            );

            ALTER TABLE subjects ADD FOREIGN KEY (id_profesor) REFERENCES profesors (id_profesor);
            ALTER TABLE profesors ADD FOREIGN KEY (id_deparment) REFERENCES deparments (id_deparment);
            ALTER TABLE evaluations ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
            ALTER TABLE profesors ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
            ALTER TABLE students ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
            ALTER TABLE personal_dates ADD FOREIGN KEY (CI_identity) REFERENCES users (CI_identity);
            ALTER TABLE careers_subjects ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
            ALTER TABLE careers ADD FOREIGN KEY (id_faculty) REFERENCES faculties (id_faculty);
            ALTER TABLE careers_years ADD FOREIGN KEY (id_career) REFERENCES careers (id_career);
            ALTER TABLE careers_subjects ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);
            ALTER TABLE students ADD FOREIGN KEY (id_career_year) REFERENCES careers_years (id_career_year);
            ALTER TABLE classes ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
            ALTER TABLE users_images ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
            ALTER TABLE evaluations ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
            ALTER TABLE classes ADD FOREIGN KEY (id_student) REFERENCES students (id_student);

            CREATE VIEW view_info_pers_student AS 
            SELECT 
                s.id_student, 
                u.id_user, 
                pd.person_n, 
                pd.last_name_1,
                pd.last_name_2, 
                s.group_student, 
                u.CI_identity, 
                directory_img
            FROM 
                students s
            INNER JOIN 
                users u ON s.id_user = u.id_user
            INNER JOIN 
                personal_dates pd ON pd.CI_identity = u.CI_identity
            LEFT JOIN 
                users_images um ON um.id_user = u.id_user;

            CREATE VIEW view_info_pers_profesor AS
            SELECT 
                pr.id_profesor, 
                u.id_user, 
                pd.person_n, 
                pd.last_name_1,
                pd.last_name_2, 
                n_deparment,
                category,
                u.CI_identity, 
                directory_img
            FROM 
                profesors pr
            INNER JOIN 
                users u ON pr.id_user = u.id_user
            INNER JOIN 
                personal_dates pd ON pd.CI_identity = u.CI_identity
            INNER JOIN 
                deparments d ON d.id_deparment = pr.id_deparment
            LEFT JOIN 
                users_images um ON um.id_user = u.id_user;

            CREATE VIEW view_profesor_subject AS
            SELECT sb.id_subject, pr.id_profesor, person_n, last_name_1, last_name_2, n_subject  FROM profesors pr
            INNER JOIN 
                subjects sb ON sb.id_profesor = pr.id_profesor
            INNER JOIN 
                view_info_pers_profesor vp ON vp.id_profesor=pr.id_profesor;

            CREATE VIEW view_subject_career AS
            SELECT cy.id_career_year, s.id_subject, crr.n_career, cy.year FROM subjects s
            INNER JOIN 
                careers_subjects cs ON cs.id_subject = s.id_subject
            INNER JOIN
                careers_years cy ON cy.id_career_year = cs.id_career_year
            INNER JOIN
                careers crr ON crr.id_career = cy.id_career
            ORDER BY cy.id_career_year;

            CREATE VIEW view_student_career AS
            SELECT s.id_student, s.id_user, cy.id_career_year, person_n, 
                    last_name_1, last_name_2, CI_identity, vs.group_student, directory_img FROM students s
            INNER JOIN
                careers_years cy ON s.id_career_year = cy.id_career_year
            INNER JOIN 
                view_info_pers_student vs ON vs.id_student = s.id_student;

)";

        PGconn *conn = PQconnectdb(connDB);

        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            return;
        }

        PGresult *res = PQexec(conn, sql.c_str());

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "SQL execution failed: " << PQerrorMessage(conn) << std::endl;
        } else {
            std::cout << "Tables created successfully" << std::endl;
        }

        PQclear(res);
        PQfinish(conn);
    }
}