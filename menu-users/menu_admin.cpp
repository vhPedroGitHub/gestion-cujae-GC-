#include "menu.h"
#include "../gc-functions/gc.h"

void submenu_add_admin(GC::DBgc *gc_db) {
    while (true) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
        std::cin.clear(); // Clear the error flag

        std::cout << "1- Agregar estudiante" << std::endl;
        std::cout << "2- Agregar profesor" << std::endl;
        std::cout << "3- Agregar admin" << std::endl;
        std::cout << "4- Agregar facultad" << std::endl;
        std::cout << "5- Agregar carrera" << std::endl;
        std::cout << "6- Agregar asignatura" << std::endl;
        std::cout << "7- Agregar departamento" << std::endl;
        std::cout << "8- Ir atras" << std::endl;
        std::cout << "Elige una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 8) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {
            case 1: 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cin.clear(); // Clear the error flag
                gc_db->addStudent("3"); 
                break;
            case 2: 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cin.clear(); // Clear the error flag
                gc_db->addProfessor("2"); 
                break;
            case 3: 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cin.clear(); // Clear the error flag
                gc_db->addUser("1"); 
                 break;
            case 4: 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cin.clear(); // Clear the error flag
                gc_db->addFaculty(); 
                break;
            case 5:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input 
                std::cin.clear(); // Clear the error flag
                gc_db->addCareer(); 
                break;
            case 6:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input 
                std::cin.clear(); // Clear the error flag
                gc_db->addSubject(); 
                break;
            case 7:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input 
                std::cin.clear(); // Clear the error flag
                gc_db->addDeparment(); 
                break;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}

void submenu_modify_admin(GC::DBgc *gc_db) {
    while (true) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input

        std::cout << "1- Modificar estudiante" << std::endl;
        std::cout << "2- Modificar profesor" << std::endl;
        std::cout << "3- Modificar admin" << std::endl;
        std::cout << "4- Modificar facultad" << std::endl;
        std::cout << "5- Modificar carrera" << std::endl;
        std::cout << "6- Modificar asignatura" << std::endl;
        std::cout << "7- Modificar departamento" << std::endl;
        std::cout << "8- Ir atras" << std::endl;
        std::cout << "Elige una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 8) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {
            case 1: std::cout << "Modificar estudiante" << std::endl; break;
            case 2: std::cout << "Modificar profesor" << std::endl; break;
            case 3: std::cout << "Modificar admin" << std::endl; break;
            case 4: std::cout << "Modificar facultad" << std::endl; break;
            case 5: std::cout << "Modificar carrera" << std::endl; break;
            case 6: std::cout << "Modificar asignatura" << std::endl; break;
            case 7: std::cout << "Modificar departamento" << std::endl; break;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}

void submenu_delete_admin(GC::DBgc *gc_db) {
    while (true) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input

        std::cout << "1- Eliminar estudiante" << std::endl;
        std::cout << "2- Eliminar profesor" << std::endl;
        std::cout << "3- Eliminar admin" << std::endl;
        std::cout << "4- Eliminar facultad" << std::endl;
        std::cout << "5- Eliminar carrera" << std::endl;
        std::cout << "6- Eliminar asignatura" << std::endl;
        std::cout << "7- Eliminar departamento" << std::endl;
        std::cout << "8- Ir atras" << std::endl;
        std::cout << "Elige una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 8) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {    
            case 1: std::cout << "Eliminar estudiante" << std::endl; break;
            case 2: std::cout << "Eliminar profesor" << std::endl; break;
            case 3: std::cout << "Eliminar admin" << std::endl; break;
            case 4: std::cout << "Eliminar facultad" << std::endl; break;
            case 5: std::cout << "Eliminar carrera" << std::endl; break;
            case 6: std::cout << "Eliminar asignatura" << std::endl; break;
            case 7: std::cout << "Eliminar departamento" << std::endl; break;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}

void submenu_verify_admin(GC::DBgc *gc_db) {
    while (true) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input

        std::cout << "1- Verificar asignaturas" << std::endl;
        std::cout << "2- Verificar carreras" << std::endl;
        std::cout << "3- Verificar alumnos" << std::endl;
        std::cout << "4- Ir atras" << std::endl;
        std::cout << "Elige una opción: ";

        int opcion;
        std::cin >> opcion;

        if (opcion == 4) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {    
            case 1: gc_db->verifiySubject(); break;
            case 2: gc_db->verifyCareersSubj(); break;
            case 3:  break;
            default:  break;
        }
    }
}

void menu_admin(USR::User *admin, GC::DBgc *gc_db) {
    std::cout << "Bienvenido " << admin->get_user_name() << std::endl;
    std::cout << "Este es el sistema de gestion CUJAE" << std::endl;

    while (true) {
        std::cout << "1- Agregar datos" << std::endl;
        std::cout << "2- Modificar datos" << std::endl;
        std::cout << "3- Eliminar datos" << std::endl;
        std::cout << "4- Verificar datos" << std::endl;
        std::cout << "5- Salir" << std::endl;
        std::cout << "Elige una opción: ";

        int opcion;
        std::cin >> opcion;

        switch (opcion) {
            case 1: submenu_add_admin(gc_db); break;
            case 2: submenu_modify_admin(gc_db); break;
            case 3: submenu_delete_admin(gc_db); break;
            case 4: submenu_verify_admin(gc_db); return;
            case 5: std::cout << "Saliendo del sistema..." << std::endl; return;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}