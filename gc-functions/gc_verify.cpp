#include "gc.h"

namespace GC {
    void DBgc::verifiySubject(){
        const std::string query = R"(SELECT * FROM subjects WHERE id_profesor IS NULL;)";
        std::vector<ConsultInd> consult = DBgc::getInfosALL(query);

        if(consult.size() > 0){
            std::cout << "Hay asignaturas sin profesores asignados" << std::endl;
        } else {
            std::cout << "Todas las asignaturas tienen profesores asignados" << std::endl;
        }
    }
}