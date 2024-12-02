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

    int getValidNumber() {
        int number;
        std::string input;

        while (true) {
            std::cout << "Ingrese un número: ";
            std::getline(std::cin, input); // Leer la línea completa

            // Verificar si la entrada es un número válido
            try {
                size_t pos; // Para verificar la posición del último carácter convertido
                number = std::stoi(input, &pos); // Convertir la cadena a entero

                // Comprobar si se han convertido todos los caracteres
                if (pos != input.length()) {
                    throw std::invalid_argument("Entrada no válida");
                }

                return number; // Retornar el número válido

            } catch (const std::invalid_argument& e) {
                std::cout << "Entrada no válida. Asegúrese de ingresar solo números." << std::endl;
            } catch (const std::out_of_range& e) {
                std::cout << "Número fuera de rango. Intente con un número más pequeño." << std::endl;
            }
        }
    }

}