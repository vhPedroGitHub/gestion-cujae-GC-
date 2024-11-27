#ifndef GC_H 
#define GC_H

#include<iostream>
#include<libpq-fe.h>
#include<string>

// Aqui se incluira todas las funciones y clases relacionadas con el funcionamiento del programa unido a la base de datos
namespace GC {

    // constantes
    extern const char* connDBG; // para conectar a la base general
    extern const char* connDB; // para conectar a la bd gc

    class DBgc { // esta clase incluye toda la funcionalidad relacionada con las operaciones en la base de datos
    private:
        PGconn *conn_gc;
    public:
        DBgc(const char*);
        ~DBgc();
        // metodos iniciales
        static void create_db_gc();
        static void create_tables_db();

        // metodos de insercion de datos 
        void addUser(std::string);
        void addProfessor(std::string);
        void addStudent(std::string);
        void addFaculty();
        void addDeparment();
        void addCareer();
        void addSubject();

        // metodos para obtener datos mediante consulta a la base de datos
        PGresult* getUserType_BD(const std::string, const std::string);

        // metodos logicos con la base de datos
        bool searchAdmin();
        bool searchUser(const std::string, const std::string);
    };

}

#endif // GC_H