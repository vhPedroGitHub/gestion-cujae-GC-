#include "gc.h"

namespace GC {

    void GC::DBgc::opcprof_passAsistence(USR::User *profesor){
        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = R"(SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user=u.id_user)";
        std::vector<ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();

        std::cout << id_profesor << std::endl;

        // obtenemos que asignaturas da el profesor y lo hacemos que elija

        // despues en que carrera, si se da el caso de que imparte la asignatura en varias carreras

        // elige uno de los grupos de esa carrera 

        // obtenemos los estudiantes 

        // pasamos la asistencia
    }

}