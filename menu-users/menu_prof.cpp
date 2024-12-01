#include "menu.h"
#include "../gc-functions/gc.h"
#include "usr.h"

void pasar_asistencia(GC::DBgc *gc_db, USR::User *profesor) {
    int sub_option;
    
    do {
        std::cout << "1. Asistencia Asistida por reconocimiento facial\n";
        std::cout << "2. Asistencia Manual\n";
        std::cout << "3. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        
        std::cin >> sub_option;

        // Validar entrada
        while (std::cin.fail() || sub_option < 1 || sub_option > 3) {
            GC::clearBufferCin();
            std::cout << "Opción no válida. Por favor, seleccione nuevamente: ";
            std::cin >> sub_option;
        }

        switch (sub_option) {
            case 1:
                // Lógica para asistencia asistida por reconocimiento facial
                gc_db->opcprof_passAsistenceAuto(profesor);
                break;
            case 2:
                gc_db->opcprof_passAsistence(profesor);
                break;
            case 3:
                // Volver al menú principal
                break;
        }
    } while (sub_option != 3);
}

void menu_profesor(USR::User *profesor, GC::DBgc *gc_db) {
    int option;
    
    do {
        std::cout << "----- Menú del Profesor -----\n";
        std::cout << "1. Pasar Asistencia\n";
        std::cout << "2. Registrar Evaluaciones\n";
        std::cout << "3. Ver alumnos invalidados por inasistencia\n";
        std::cout << "4. Ver evaluaciones de los alumnos\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opción: ";
        
        std::cin >> option;

        // Validar entrada
        while (std::cin.fail() || option < 1 || option > 5) {
            GC::clearBufferCin();
            std::cout << "Opción no válida. Por favor, seleccione nuevamente: ";
            std::cin >> option;
        }

        switch (option) {
            case 1:
                pasar_asistencia(gc_db, profesor); // Llamar a la función del submenú
                break;

            case 2:
                // Lógica para registrar evaluaciones
                std::cout << "Registrar evaluaciones seleccionada.\n";
                break;

            case 3:
                // Lógica para ver alumnos invalidados por inasistencia
                std::cout << "Ver alumnos invalidados por inasistencia seleccionada.\n";
                break;

            case 4:
                // Lógica para ver evaluaciones de los alumnos
                std::cout << "Ver evaluaciones de los alumnos seleccionada.\n";
                break;

            case 5:
                // Salir del menú
                std::cout << "Saliendo del menú...\n";
                break;
        }

    } while (option != 5);
}
