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
        std::cout << "8- Agregar imagen a un usuario" << std::endl;
        std::cout << "9- Ir atras" << std::endl;
        std::cout << "Elige una opción" << std::endl;

        int opcion = GC::getValidNumber();

        if (opcion == 9) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {
            case 1: 
                GC::clearBufferCin();
                gc_db->addStudent("3"); 
                break;
            case 2: 
                GC::clearBufferCin();
                gc_db->addProfessor("2"); 
                break;
            case 3: 
                GC::clearBufferCin();
                gc_db->addUser("1"); 
                 break;
            case 4: 
                GC::clearBufferCin();
                gc_db->addFaculty(); 
                break;
            case 5:
                GC::clearBufferCin();
                gc_db->addCareer(); 
                break;
            case 6:
                GC::clearBufferCin();
                gc_db->addSubject(); 
                break;
            case 7:
                GC::clearBufferCin();
                gc_db->addDeparment(); 
                break;
            case 8:
                GC::clearBufferCin();
                gc_db->addImage(); 
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
        std::cout << "2- Salir" << std::endl;
        std::cout << "Elige una opción" << std::endl;

        int opcion = GC::getValidNumber();

        if (opcion == 2) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {
            case 1: 
            gc_db->updateStudent();
            break;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}

void submenu_delete_admin(GC::DBgc *gc_db) {
    while (true) {
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input

        std::cout << "1- Eliminar estudiante" << std::endl;
        std::cout << "2- Salir" << std::endl;
        std::cout << "Elige una opción" << std::endl;

        int opcion = GC::getValidNumber();

        if (opcion == 2) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {
            case 1:
                gc_db->deleteStudent();
                break;
            default:
                break;
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
        std::cout << "Elige una opción" << std::endl;

        int opcion = GC::getValidNumber();

        if (opcion == 4) break;

        // Aquí puedes agregar la lógica para cada opción
        switch (opcion) {    
            case 1: gc_db->verifiySubject(); break;
            case 2: gc_db->verifyCareersSubj(); break;
            case 3: gc_db->verifyStudentsCar(); break;
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
        std::cout << "Elige una opción" << std::endl;

        int opcion = GC::getValidNumber();

        switch (opcion) {
            case 1: submenu_add_admin(gc_db); break;
            case 2: submenu_modify_admin(gc_db); break;
            case 3: submenu_delete_admin(gc_db); break;
            case 4: submenu_verify_admin(gc_db); break;
            case 5: std::cout << "Saliendo del sistema..." << std::endl; return;
            default: std::cout << "Opción no válida, intenta de nuevo." << std::endl; break;
        }
    }
}