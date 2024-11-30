#include "gc.h"

namespace GC {
    void clearBufferCin(){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag
    }
}