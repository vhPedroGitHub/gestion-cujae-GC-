#include "gc.h"

std::string number_range(int min, int max) {
    int numero;
    
    while (true) {
        std::cout << "Por favor, ingresa un número entre " << min << " y " << max << ": ";
        
        // Leer el número
        std::cin >> numero;

        // Verificar si la entrada es válida
        if (std::cin.fail() || numero < min || numero > max) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            std::cout << "Entrada no válida. Inténtalo de nuevo." << std::endl;
        } else {
            // Convertir el número a string y devolverlo
            return std::to_string(numero);
        }
    }
}

namespace GC {
    void clearBufferCin(){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag
    }
}