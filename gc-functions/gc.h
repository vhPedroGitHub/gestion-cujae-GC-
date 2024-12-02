#ifndef GC_H 
#define GC_H

#include<iostream>
#include<libpq-fe.h>
#include<string>
#include<vector>
#include<limits>
#include<opencv2/highgui.hpp>
#include<opencv2/dnn.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include "../menu-users/usr.h"

std::string number_range(int, int);

// Aqui se incluira todas las funciones y clases relacionadas con el funcionamiento del programa unido a la base de datos
namespace GC {

    // constantes
    extern const char* connDBG; // para conectar a la base general
    extern const char* connDB; // para conectar a la bd gc

    class ConsultInd {
        private:
            std::string value, indice;
        public:
            ConsultInd(const std::string, const std::string);
            std::string getValue();
            std::string getIndice();
    };

    std::string selectElement( std::vector<ConsultInd>);

    void clearBufferCin();
    int getValidNumber();

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
        void addImage();
        static void addClass(const std::string, const std::string, const std::string, const std::string, const std::string);
        static void addEval(std::string, std::string, std::string, std::string, std::string);

        // metodos para insertar datos
        void updateStudent();

        // deletes
        void deleteStudent();

        // metodos para obtener datos mediante consulta a la base de datos
        PGresult* getUserType_BD(const std::string, const std::string);
        static std::vector<ConsultInd> getInfos(const std::string& , const std::string& , const std::string& );
        static std::vector<ConsultInd> getInfosALL(const std::string&);

        // metodos logicos con la base de datos
        static bool searchEmptyElements(DBgc *);
        bool searchUser(const std::string, const std::string);

        // funciones de verificacion (su objetivo es revisar los registros de cada tabla)
        void verifiySubject();
        void verifyCareersSubj();
        void verifyStudentsCar();

        // operaciones realizadas por el profesor
        void opcprof_passAsistence(USR::User *);
        void opcprof_passAsistenceAuto(USR::User *);
        void opcprof_addEval(USR::User *);
        void opcprof_seeAssis(USR::User *);
    };

}

#endif // GC_H