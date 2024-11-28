#include "gc.h"

namespace GC {
    ConsultInd::ConsultInd(const std::string _value, const std::string _indice){
        value = _value;
        indice = _indice;
    }

    std::string ConsultInd::getValue(){return value;}
    std::string ConsultInd::getIndice(){return indice;}
}