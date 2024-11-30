#include "gc.h"

namespace GC {
    void DBgc::verifiySubject(){
        std::string query = R"(SELECT * FROM subjects WHERE id_profesor IS NULL;)";
        std::vector<ConsultInd> consult = DBgc::getInfosALL(query);

        if(consult.size() > 0){
            std::cout << "Hay asignaturas sin profesores asignados" << std::endl;
            std::cout << "Ahora por cada asignatura debera de asignarle uno de los profesores" << std::endl;


            query = R"(SELECT id_profesor, person_n, last_name_1, category, n_deparment FROM (
                                SELECT * FROM (
                                    SELECT * FROM (
                                        (SELECT * FROM profesors prof 
                                        INNER JOIN users usr ON prof.id_user = usr.id_user)
                                    ) AS prouser INNER JOIN personal_dates per ON per.CI_identity = prouser.CI_identity  
                                ) AS sub1 INNER JOIN deparments d ON sub1.id_deparment = d.id_deparment
                            ) AS profesor;
                        )";

            std::vector<ConsultInd> profesors = DBgc::getInfosALL(query);

            for (auto asignature : consult){
                std::cout << "Asignatura: " << asignature.getValue() << std::endl;
                std::cout << "Seleccione un profesor para esta asignatura. Los profesores disponibles son: " << std::endl;
                
                std::string id_profesor = selectElement(profesors);

                std::string sql = "UPDATE subjects SET id_profesor = " + id_profesor +
                      " WHERE id_subject = " + asignature.getIndice() + ";";

                PGresult *res = PQexec(conn_gc, sql.c_str());

                if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                    std::cerr << "Error en la actualización: " << PQerrorMessage(conn_gc) << std::endl;
                } else {
                    std::cout << "Actualización completada." << std::endl;
                }

                PQclear(res);
            }
            
        } else {
            std::cout << "Todas las asignaturas tienen profesores asignados" << std::endl;
        }
    }

    void DBgc::verifyCareersSubj(){
        std::string query = R"(SELECT id_career_year, n_career, year FROM (
                                SELECT * FROM (
                                    SELECT * FROM (
                                        SELECT cy.id_career_year, year, id_career_subject, id_career FROM careers_years cy 
                                        LEFT JOIN careers_subjects cs ON cy.id_career_year=cs.id_career_year		  
                                    ) AS consult
                                ) AS consult2
                                WHERE id_career_subject IS NULL
                            ) AS consult3 INNER JOIN careers crer ON crer.id_career=consult3.id_career;)";

        std::vector<ConsultInd> consult = DBgc::getInfosALL(query);

        if(consult.size() > 0){
            std::cout << "Hay carreras sin asignaturas asignadas" << std::endl;
            std::cout << "Ahora por cada una de estas carreras debe de asignarle una o varias asignaturas" << std::endl;


            query = R"(SELECT id_subject, n_subject, person_n, last_name_1, category, n_deparment FROM subjects s
                        INNER JOIN (SELECT id_profesor, person_n, last_name_1, category, n_deparment FROM (
                                    SELECT * FROM (
                                        SELECT * FROM (
                                            (SELECT * FROM profesors prof 
                                            INNER JOIN users usr ON prof.id_user = usr.id_user)
                                        ) AS prouser INNER JOIN personal_dates per ON per.CI_identity = prouser.CI_identity  
                                    ) AS sub1 INNER JOIN deparments d ON sub1.id_deparment = d.id_deparment
                                ) AS profesor) AS prof
                        ON s.id_profesor=prof.id_profesor;
                        )";

            std::vector<ConsultInd> subject = DBgc::getInfosALL(query);

            for (auto career : consult){
                std::cout << "Carrera: " << career.getValue() << std::endl;
                while (true){

                    std::cout << "Seleccione una asignatura para esta carrera." << std::endl;
                    std::cout << "Las asignaturas disponibles son: " << std::endl;
                    
                    std::string id_subject = selectElement(subject);

                    const char *paramsValues[2]={id_subject.c_str(), career.getIndice().c_str()};

                    PGresult *res = PQexecParams(conn_gc, "INSERT INTO careers_subjects (id_subject, id_career_year) VALUES ($1, $2)",
                                                2,
                                                NULL,
                                                paramsValues,
                                                NULL,
                                                NULL,
                                                0);

                    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                        std::cerr << "Error en la actualización: " << PQerrorMessage(conn_gc) << std::endl;
                    } else {
                        std::cout << "Se agrego correctamento la asignatura a la carrera." << std::endl;
                    }

                    PQclear(res);

                    std::cin.clear(); // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input

                    std::string salida;
                    std::cout << "Desea dejar de agregar asignaturas a esa carrera digite s -> "; std::getline(std::cin, salida);

                    if (salida == "s"){break;} 
                }
            }
            
        } else {
            std::cout << "Todas las asignaturas tienen profesores asignados" << std::endl;
        }
    }

    void DBgc::verifyStudentsCar(){
        std::string query = R"(SELECT * FROM students WHERE id_career_year IS NULL;)";
        std::vector<ConsultInd> consult = DBgc::getInfosALL(query);

        if(consult.size() > 0){
            std::cout << "Hay estudiantes que aun no tienen una carrera universitaria" << std::endl;
            std::cout << "Ahora por cada estudiante debe de ingresar que carrera asignarle" << std::endl;

            query = R"(SELECT id_career_year, n_career, year FROM careers_years cy
                        INNER JOIN careers cr ON cy.id_career=cr.id_career;)";

            std::vector<ConsultInd> careers = DBgc::getInfosALL(query);

            for (auto student : consult){
                std::cout << "Alumno: " << student.getValue() << std::endl;
                std::cout << "Seleccione una carrera para este alumno. Las carreras disponibles son: " << std::endl;
                
                std::string id_career_year = selectElement(careers);

                std::string sql = "UPDATE students SET id_career_year = " + id_career_year +
                      " WHERE id_student = " + student.getIndice() + ";";

                PGresult *res = PQexec(conn_gc, sql.c_str());

                if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                    std::cerr << "Error en la actualización: " << PQerrorMessage(conn_gc) << std::endl;
                } else {
                    std::cout << "Actualización completada." << std::endl;
                }

                PQclear(res);
            }
            
        } else {
            std::cout << "Todos los estudiantes estan estudiando una carrera" << std::endl;
        }
    }
}