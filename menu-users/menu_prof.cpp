#include "menu.h"
#include "../gc-functions/gc.h"
#include "usr.h"

void pasar_asistencia(GC::DBgc *gc_db, USR::User *profesor) {
    int option;
    do {
        std::cout << "1. Asistencia Asistida por reconocimiento facial\n";
        std::cout << "2. Asistencia Manual\n";
        std::cout << "3. Volver al menú principal\n";
        std::cout << "Elige una opción" << std::endl;

        option = GC::getValidNumber();

        // Validar entrada
        while (std::cin.fail() || option < 1 || option > 3) {
            std::cout << "Elige una opción" << std::endl;
            option = GC::getValidNumber();
        }

        switch (option) {
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
    } while (option != 3);
}

void menu_profesor(USR::User *profesor, GC::DBgc *gc_db) {
    int option;
    
    do {
        std::cout << "----- Menú del Profesor -----\n";
        std::cout << "1. Pasar Asistencia\n";
        std::cout << "2. Registrar Evaluaciones\n";
        std::cout << "3. Ver asistencia de los estudiantes\n";
        std::cout << "4. Salir\n";
        std::cout << "Elige una opción" << std::endl;

        option = GC::getValidNumber();

        switch (option) {
            case 1:
                pasar_asistencia(gc_db, profesor); // Llamar a la función del submenú
                break;

            case 2:
                // Lógica para registrar evaluaciones
                gc_db->opcprof_addEval(profesor);
                break;

            case 3:
                // Salir del menú
                gc_db->opcprof_seeAssis(profesor);
                break;
            case 4:
                std::cout << "Saliendo del menu ...." << std::endl;
                break;
        }

    } while (option != 4);
}
