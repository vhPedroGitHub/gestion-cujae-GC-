#include "./menu.h"
#include "../gc-functions/gc.h"

// Para std::numeric_limits
int get_number_range(int min, int max) {
    int number;

    while (true) {
        std::cout << "Introduce un número entre " << min << " y " << max << ": ";
        std::cin >> number;

        // Verificar si la entrada es un número válido y está en el rango
        if (std::cin.fail() || number < min || number > max) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Entrada no válida. Por favor, inténtalo de nuevo." << std::endl;
        } else {
            break;
        }
    }

    return number;
}

void menu_profesor(USR::Profesor *profesor, GC::DBgc *gc_db){
    
}

void menu_student(USR::Student *student, GC::DBgc *gc_db){
    
}