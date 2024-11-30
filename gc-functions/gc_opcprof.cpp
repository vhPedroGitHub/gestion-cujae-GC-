#include "gc.h"
#include <ctime>
#include <iomanip>

std::string gettingTime() {
    // Obtener el tiempo actual
    std::time_t t = std::time(nullptr);
    // Convertir a tiempo local
    std::tm* now = std::localtime(&t);

    // Crear un buffer para almacenar la fecha formateada
    char buffer[11]; // Formato "yy-mm-dd" + terminador nulo

    // Formatear la fecha
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);

    return std::string(buffer); // Devolver como string
}

namespace GC {

    void DBgc::opcprof_passAsistence(USR::User *profesor){
        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = "SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user = " + profesor->get_id_user() + ";";
        std::vector<ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();
        std::cout << "El id del profesor es " << id_profesor << std::endl;
        // obtenemos que asignaturas da el profesor y lo hacemos que elija

        query = "SELECT * FROM view_profesor_subject WHERE id_profesor = " + id_profesor + ";";
        consult = GC::DBgc::getInfosALL(query);

        std::cout << "Diga en que asignatura desea pasar la asistencia" << std::endl;
        std::string id_subject = selectElement(consult);
        clearBufferCin();

        std::string cantidad_turnos; 
        std::cout << "Cuantos turnos dio de esa clase"; std::getline(std::cin, cantidad_turnos);

        // despues en que carrera desea pasar la asistencia, si se da el caso de que imparte la asignatura en varias carreras
        query = "SELECT * FROM view_subject_career WHERE id_subject = " + id_subject + ";";
        consult = GC::DBgc::getInfosALL(query);

        std::cout << "Se detecto que imparte esa asignatura en estas carreras, debe seleccionar una" << std::endl;
        std::string id_career_year = selectElement(consult);
        clearBufferCin();

        // elige uno de los grupos de esa carrera 
        PGresult *res = PQexec(conn_gc, ("SELECT MAX(group_student) FROM view_student_career WHERE id_career_year = " + id_career_year + ";").c_str());
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        std::string groups = PQgetvalue(res, 0, 0);
        std::cout << "Hay un total de " << groups << " grupos. Digite un numero que se encuentre en el rango de los grupos" << std::endl;

        std::string group = number_range(1, std::stoi(groups));

        // obtenemos los estudiantes 
        const char *paramValues[2]={id_career_year.c_str(), group.c_str()};
        res = PQexecParams(conn_gc, R"(SELECT * FROM view_student_career 
                                            WHERE id_career_year = $1 AND group_student = $2;)", 
                                            2, NULL, paramValues, NULL, NULL, 0);
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        std::string date, entry;
        clearBufferCin();
        std::cout << "Antes de continuar digite la fecha en formato yyyy-mm-dd o digite /c si desea obtenerla desde la PC" << std::endl;
        std::cout << "Digite la fecha -> "; std::getline(std::cin, date);

        date = date=="/c" ?  gettingTime() : date; 

        // a partir de aqui ya se obtuvieron los estudiantes del grupo al cual se le pasara la asistencia.
        // por cada estudiante le mostraremos el nombre en pantalla al profesor y el simplemente escribira
        // s si fue el estudiante o n si no fue. Asi hasta que termine la operacion

        int studentsNfields = PQntuples(res);
        int studentsNfcolumns = PQnfields(res);
        std::cout << "Hay un total de " << studentsNfields << " estudiantes" << std::endl;

        for (int i = 0; i < studentsNfields; i++) {
            std::cout << "El estudiante: " << PQgetvalue(res, i, 3) << " " << PQgetvalue(res, i, 4) << " " << PQgetvalue(res, i, 5) << std::endl;

            std::cout << "Digite s = si asistio ||| n = no asistio -> "; std::getline(std::cin, entry);

            if (entry == "s"){
                DBgc::addClass(id_subject, PQgetvalue(res, i, 0), cantidad_turnos, date, "true");
            } else if (entry == "n") {
                DBgc::addClass(id_subject, PQgetvalue(res, i, 0), cantidad_turnos, date, "false");
            }

        }
        
    }

}