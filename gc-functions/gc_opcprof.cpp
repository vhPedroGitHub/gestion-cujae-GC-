#include "gc.h"
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h>

#include "../vision_computer/const.h"

std::string gettingTime() {
    // Obtener el tiempo actual
    std::time_t t = std::time(nullptr);
    // Convertir a tiempo local
    std::tm* now = std::localtime(&t);

    // Crear un buffer para almacenar la fecha formateada
    char buffer[11]; // Formato "yy-mm-dd" + terminador nulo

    // Formatear la fecha
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);

    return std::string(buffer); // Devolver como string
}

std::string getDates(){
    std::string date, entry;
    GC::clearBufferCin();
    std::cout << "Antes de continuar digite la fecha en formato yyyy-mm-dd o digite /c si desea obtenerla desde la PC" << std::endl;
    std::cout << "Digite la fecha -> "; std::getline(std::cin, date);

    date = date=="/c" ?  gettingTime() : date; 

    return date;
}

class IMGS_student {
    public:
        std::string id_student, id_career_year, id_user, person_n, last_name_1, last_name_2, CI_identity, group_student;
        std::vector<cv::Mat> imgs;
        std::vector<cv::Mat> imgs_compare;
        bool assis = false;

        IMGS_student(PGresult *res, PGconn *conn_gc, int i){
            id_student = PQgetvalue(res, i, 0); id_user = PQgetvalue(res, i, 1); person_n = PQgetvalue(res, i, 3);
            last_name_1 = PQgetvalue(res, i, 4); last_name_2 = PQgetvalue(res, i, 5); CI_identity = PQgetvalue(res, i, 6);
            group_student = PQgetvalue(res, i, 7); id_career_year = PQgetvalue(res, i, 2);

            // obtendremos las imagenes que identifican al estudiante
            const char *paramValues[1]={id_student.c_str()};
            PGresult *resul = PQexecParams(conn_gc, R"(SELECT directory_img FROM view_student_career 
                                                WHERE id_student = $1;)", 
                                            1, NULL, paramValues, NULL, NULL, 0);

            std::cout << PQgetvalue(res, i, 8) << std::endl;

            for (int j = 0; j < PQntuples(resul); j++){
                cv::Mat img = cv::imread(PQgetvalue(resul, j, 0));
                cv::resize(img, img, cv::Size(320, 320));
                imgs.push_back(img);
            }
        }

        void insertIMGcompare(cv::Mat I){
            imgs_compare.push_back(I);
        }
};

namespace GC {

    void DBgc::opcprof_passAsistence(USR::User *profesor){

        std::string date = getDates(), entry;

        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = "SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user = " + profesor->get_id_user() + ";";
        std::vector<GC::ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();
        std::cout << "El id del profesor es " << id_profesor << std::endl;
        // obtenemos que asignaturas da el profesor y lo hacemos que elija

        query = "SELECT * FROM view_profesor_subject WHERE id_profesor = " + id_profesor + ";";
        consult = GC::DBgc::getInfosALL(query);

        if(consult.size() == 0){
            std::cout << "Debe impartir una asignatura para poder pasar asistencia" << std::endl;
            return; 
        }
        std::cout << "Diga en que asignatura desea pasar la asistencia" << std::endl;
        std::string id_subject = GC::selectElement(consult);
        GC::clearBufferCin();

        std::string cantidad_turnos; 
        std::cout << "Cuantos turnos dio de esa clase"; std::getline(std::cin, cantidad_turnos);

        // despues en que carrera desea pasar la asistencia, si se da el caso de que imparte la asignatura en varias carreras
        query = "SELECT * FROM view_subject_career WHERE id_subject = " + id_subject + ";";
        consult = GC::DBgc::getInfosALL(query);

        std::cout << "Se detecto que imparte esa asignatura en estas carreras, debe seleccionar una" << std::endl;
        std::string id_career_year = selectElement(consult);
        GC::clearBufferCin();

        // elige uno de los grupos de esa carrera 
        PGresult *res = PQexec(conn_gc, ("SELECT MAX(group_student) FROM view_student_career WHERE id_career_year = " + id_career_year + ";").c_str());
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        std::string groups = PQgetvalue(res, 0, 0);
        std::cout << "Hay un total de " << groups << " grupos. Digite un numero que se encuentre en el rango de los grupos" << std::endl;

        std::string group = number_range(1, std::stoi(groups));

        // obtenemos los estudiantes 
        const char *paramValues[2]={id_career_year.c_str(), group.c_str()};
        res = PQexecParams(conn_gc, R"(SELECT DISTINCT ON (id_student) id_student, id_user, id_career_year, person_n, 
		                            last_name_1, last_name_2, CI_identity, group_student, directory_img FROM view_student_career 
                                            WHERE id_career_year = $1 AND group_student = $2;)", 
                                            2, NULL, paramValues, NULL, NULL, 0);
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        int studentsNfields = PQntuples(res);
        int studentsNfcolumns = PQnfields(res);
        std::cout << "Hay un total de " << studentsNfields << " estudiantes" << std::endl;

        clearBufferCin();
        for (int i = 0; i < studentsNfields; i++) {
            std::cout << "El estudiante: " << PQgetvalue(res, i, 3) << " " << PQgetvalue(res, i, 4) << " " << PQgetvalue(res, i, 5) << std::endl;

            std::cout << "Digite s = si asistio ||| n = no asistio -> "; std::getline(std::cin, entry);

            if (entry == "s"){
                DBgc::addClass(id_subject, PQgetvalue(res, i, 0), cantidad_turnos, date, "true");
            } else if (entry == "n") {
                DBgc::addClass(id_subject, PQgetvalue(res, i, 0), cantidad_turnos, date, "false");
            }

        }

        PQclear(res);
    }

    void DBgc::opcprof_passAsistenceAuto(USR::User *profesor){
        std::string date = getDates(), entry;
        
        // a partir de aqui ya se obtuvieron los estudiantes del grupo al cual se le pasara la asistencia.
        // por cada estudiante le mostraremos el nombre en pantalla al profesor y el simplemente escribira
        // s si fue el estudiante o n si no fue. Asi hasta que termine la operacion

        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = "SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user = " + profesor->get_id_user() + ";";
        std::vector<GC::ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();
        std::cout << "El id del profesor es " << id_profesor << std::endl;
        // obtenemos que asignaturas da el profesor y lo hacemos que elija

        query = "SELECT * FROM view_profesor_subject WHERE id_profesor = " + id_profesor + ";";
        consult = GC::DBgc::getInfosALL(query);

        if(consult.size() == 0){
            std::cout << "Debe impartir una asignatura para poder pasar asistencia" << std::endl;
            return; 
        }
        std::cout << "Diga en que asignatura desea pasar la asistencia" << std::endl;
        std::string id_subject = GC::selectElement(consult);
        GC::clearBufferCin();

        std::string cantidad_turnos; 
        std::cout << "Cuantos turnos dio de esa clase"; std::getline(std::cin, cantidad_turnos);

        // despues en que carrera desea pasar la asistencia, si se da el caso de que imparte la asignatura en varias carreras
        query = "SELECT * FROM view_subject_career WHERE id_subject = " + id_subject + ";";
        consult = GC::DBgc::getInfosALL(query);

        std::cout << "Se detecto que imparte esa asignatura en estas carreras, debe seleccionar una" << std::endl;
        std::string id_career_year = selectElement(consult);
        GC::clearBufferCin();

        // elige uno de los grupos de esa carrera 
        PGresult *res = PQexec(conn_gc, ("SELECT MAX(group_student) FROM view_student_career WHERE id_career_year = " + id_career_year + ";").c_str());
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        std::string groups = PQgetvalue(res, 0, 0);
        std::cout << "Hay un total de " << groups << " grupos. Digite un numero que se encuentre en el rango de los grupos" << std::endl;

        std::string group = number_range(1, std::stoi(groups));

        // obtenemos los estudiantes 
        const char *paramValues[2]={id_career_year.c_str(), group.c_str()};
        res = PQexecParams(conn_gc, R"(SELECT DISTINCT ON (id_student) id_student, id_user, id_career_year, person_n, 
		                            last_name_1, last_name_2, CI_identity, group_student, directory_img FROM view_student_career 
                                            WHERE id_career_year = $1 AND group_student = $2;)", 
                                            2, NULL, paramValues, NULL, NULL, 0);
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        int studentsNfields = PQntuples(res);
        int studentsNfcolumns = PQnfields(res);
        std::cout << "Hay un total de " << studentsNfields << " estudiantes" << std::endl;

        //----------------------------------------------------------------------------------------------
        // recorremos cada estudiante del grupo para recopilar sus imagenes que seran procesadas despues
        //----------------------------------------------------------------------------------------------
        std::vector<IMGS_student> students_imgs;
        for (int i = 0; i < studentsNfields; i++) {
            students_imgs.push_back( IMGS_student(res, conn_gc, i) );
        }
        std::cout << "Se han cargado todos los estudiantes con las imagenes que lo identifican" << std::endl;

        // cargamos los modelos a utilizar
        // Inicializamos los modelos
        cv::Ptr<cv::FaceDetectorYN> detector = cv::FaceDetectorYN::create(FD_MODELPATH, "", cv::Size(MAX_WIDTH, MAX_HEIGHT), SCORE_THRESHOLD, NMS_THRESHOLD, TOP_K);
        cv::Ptr<cv::FaceRecognizerSF> recognition = cv::FaceRecognizerSF::create(FR_MODELPATH, "");
        // a partir de aqui le pedimos al profesor que indique el nombre de la imagen de la clase donde se pasara la asistencia
        while (true){
            clearBufferCin();
            std::string directory_class = "../sources/class_images/";
            std::cout << "Digite el nombre con la extension de la imagen de la clase -> "; std::getline(std::cin, entry);
            directory_class += entry;

            cv::Mat class_img = cv::imread(directory_class);

            // En este paso tenemos las imagenes de los estudiantes del grupo elegido y la imagen de la clase
            // dada por el profesor
            // pasos a seguir: 
            // 1- analizamos la imagen brindada por el profesor, detectando los rostros que hay en ella
            // 2- recorremos cada rostro de la imagen y lo comparamos con los rostros que tenemos de los estudiantes
            // 3- cuando estemos analizando el parentezco si los indices dan favorables, guardaremos la imagen comparada
            //  dentro de un vector llamado image_compare
            // 4- el objetivo final es recopilar que imagenes se parecieron para mostrarle al profesor
            // mire detecte este rostro y se parece a este estudiante, es verdad s = si, n = no
            // si dice que si el profesor se le dara la asistencia al alumno, sino no ocurre nada hasta el final.

            cv::Mat class_detect_faces; 
            cv::Mat alignImage1, alignImage2;
            detector->setInputSize(class_img.size());
            detector->detect(class_img, class_detect_faces);

            std::cout << class_detect_faces.rows << endl;

            // hacemos un blucle for que recorra cada uno de los rostros
            for (int i = 0; i < class_detect_faces.rows; i++){

                recognition->alignCrop(class_img, class_detect_faces.row(i), alignImage1);
                
                for (IMGS_student& img_student : students_imgs){

                    for (cv::Mat &img : img_student.imgs){
                        // aqui compararemos cada imagen de los estudiantes con el rostro detectado
                        std::cout << "procesando" << std::endl;
                        cv::Mat face_detect;
                        detector->setInputSize(img.size());
                        detector->detect(img, face_detect);

                        recognition->alignCrop(img, face_detect, alignImage2);

                        cv::Mat faceFeature1, faceFeature2;
                        recognition->feature(alignImage1, faceFeature1);
                        faceFeature1 = faceFeature1.clone();
                        recognition->feature(alignImage2, faceFeature2);
                        faceFeature2 = faceFeature2.clone();

                        double cos = recognition->match(faceFeature1, faceFeature2, cv::FaceRecognizerSF::DisType::FR_COSINE);
                        double lnormal = recognition->match(faceFeature1, faceFeature2, cv::FaceRecognizerSF::DisType::FR_NORM_L2);

                        if(cos > cosine_similar_thresh || lnormal < l2norm_similar_thresh){
                            int x = class_detect_faces.row(i).at<float>(0, 0);
                            int y = class_detect_faces.row(i).at<float>(0, 1);
                            int w = class_detect_faces.row(i).at<float>(0, 2);
                            int h = class_detect_faces.row(i).at<float>(0, 3);

                            cv::Mat copyMat = class_img.clone();
                            rectangle(copyMat, cv::Rect2d(cv::Point2d(x, y), cv::Size2d(w, h)), cv::Scalar(0,255,0), 4, 8, 0);
                            cv::resize(copyMat, copyMat, cv::Size(320, 320));

                            img_student.insertIMGcompare(copyMat);
                            std::cout << "Se ha detectado una concidencia" << std::endl;
                            std::cout << img_student.imgs_compare.size() << std::endl;
                        }
                    }
                }
            }
                
            std::cout << "Ha terminado el proceso de analisis \n";
            std::cout << "Si desea agregar otra imagen digite s -> "; std::getline(std::cin, entry);

            if(entry != "s"){
                break;
            }
        }

        for (IMGS_student& img_st : students_imgs){
            std::cout << "Estudiante: " << img_st.person_n << " " << img_st.last_name_1 << " " << img_st.last_name_2 << std::endl;
            std::cout << "A continuacion se determinara su asistencia" << std::endl;
            std::cout << img_st.imgs_compare.size() << std::endl;
                
            for (cv::Mat compare_img : img_st.imgs_compare){
                cv::imshow("estudiante", img_st.imgs[0]);
                cv::imshow("foto clase", compare_img);

                cv::moveWindow("estudiante", 10, 10);
                cv::moveWindow("foto clase", 330, 10);
                cv::pollKey();

                std::cout << "Digite s = si es el estudiante ||| n = hay alguna duda -> "; std::getline(std::cin, entry);

                if (entry == "s"){
                    DBgc::addClass(id_subject, img_st.id_student, cantidad_turnos, date, "true");
                    img_st.assis = true;
                    cv::destroyAllWindows();
                    break;
                }

                cv::destroyAllWindows();
            }

            if (img_st.imgs_compare.size() == 0 || entry == "n"){
                DBgc::addClass(id_subject, img_st.id_student, cantidad_turnos, date, "false");
                img_st.assis = false;
            }
        }
    }

    void DBgc::opcprof_addEval(USR::User *profesor){
        std::string date = getDates(), entry;
        
        // a partir de aqui ya se obtuvieron los estudiantes del grupo al cual se le pasara la asistencia.
        // por cada estudiante le mostraremos el nombre en pantalla al profesor y el simplemente escribira
        // s si fue el estudiante o n si no fue. Asi hasta que termine la operacion

        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = "SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user = " + profesor->get_id_user() + ";";
        std::vector<GC::ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();
        std::cout << "El id del profesor es " << id_profesor << std::endl;
        // obtenemos que asignaturas da el profesor y lo hacemos que elija

        query = "SELECT * FROM view_profesor_subject WHERE id_profesor = " + id_profesor + ";";
        consult = GC::DBgc::getInfosALL(query);

        if(consult.size() == 0){
            std::cout << "Debe impartir una asignatura para poder pasar asistencia" << std::endl;
            return; 
        }
        std::cout << "Diga en que asignatura desea pasar la asistencia" << std::endl;
        std::string id_subject = GC::selectElement(consult);
        GC::clearBufferCin();

        // despues en que carrera desea pasar la asistencia, si se da el caso de que imparte la asignatura en varias carreras
        query = "SELECT * FROM view_subject_career WHERE id_subject = " + id_subject + ";";
        consult = GC::DBgc::getInfosALL(query);

        std::cout << "Se detecto que imparte esa asignatura en estas carreras, debe seleccionar una" << std::endl;
        std::string id_career_year = selectElement(consult);
        GC::clearBufferCin();

        // elige uno de los grupos de esa carrera 
        PGresult *res = PQexec(conn_gc, ("SELECT MAX(group_student) FROM view_student_career WHERE id_career_year = " + id_career_year + ";").c_str());
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        std::string groups = PQgetvalue(res, 0, 0);
        std::cout << "Hay un total de " << groups << " grupos. Digite un numero que se encuentre en el rango de los grupos" << std::endl;

        std::string group = number_range(1, std::stoi(groups));

        // obtenemos los estudiantes 
        const char *paramValues[2]={id_career_year.c_str(), group.c_str()};
        res = PQexecParams(conn_gc, R"(SELECT DISTINCT ON (id_student) id_student, id_user, id_career_year, person_n, 
		                            last_name_1, last_name_2, CI_identity, group_student, directory_img FROM view_student_career 
                                            WHERE id_career_year = $1 AND group_student = $2;)", 
                                            2, NULL, paramValues, NULL, NULL, 0);
        
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            std::cerr << "Error" << PQerrorMessage(conn_gc) << std::endl;
            PQclear(res);
        }

        int studentsNfields = PQntuples(res);
        int studentsNfcolumns = PQnfields(res);
        std::cout << "Hay un total de " << studentsNfields << " estudiantes" << std::endl;
        clearBufferCin();
        std::string type_eval;
        std::cout << "Digite el tipo de evaluacion que realizo -> "; std::getline(std::cin, type_eval);

        for (int i = 0; i < studentsNfields; i++) {
            std::string calification;
            std::cout << "El estudiante: " << PQgetvalue(res, i, 3) << " " << PQgetvalue(res, i, 4) << " " << PQgetvalue(res, i, 5) << std::endl;

            std::cout << "Digite la clasificacion del estudiante" << std::endl;

            calification = std::to_string(GC::getValidNumber());
            
            DBgc::addEval(id_subject, PQgetvalue(res, i, 0), calification, 
                type_eval, date);
        }

        PQclear(res);
    }   

    void DBgc::opcprof_seeAssis(USR::User *profesor){
        // primero obtenemos el id del profesor correspondiente al usuario logueado
        std::string query = "SELECT u.id_user, ('anonimo') aux FROM users u INNER JOIN profesors pr ON pr.id_user = " + profesor->get_id_user() + ";";
        std::vector<GC::ConsultInd> consult = GC::DBgc::getInfosALL(query);
        
        std::string id_profesor = consult[0].getIndice();
        std::cout << "El id del profesor es " << id_profesor << std::endl;

        query = "SELECT * FROM view_profesor_subject WHERE id_profesor = " + id_profesor + ";";
        consult = GC::DBgc::getInfosALL(query);

        if(consult.size() == 0){
            std::cout << "Debe impartir una asignatura para poder pasar asistencia" << std::endl;
            return; 
        }

        std::cout << "Diga en que asignatura desea ver la asistencia" << std::endl;
        std::string id_subject = GC::selectElement(consult);
        GC::clearBufferCin();
        
        query = R"(SELECT SUM(ct) FROM (
                    SELECT DISTINCT ON(date_class) SUM(cantidad_turnos) AS ct FROM classes
                    WHERE id_subject = $1
                    GROUP BY id_classe
                ) AS cttable;)";

        const char *paramValue_1[1] = {id_subject.c_str()};
        PGresult *res = PQexecParams(conn_gc, query.c_str(), 1, NULL, paramValue_1, NULL, NULL, 0);

        std::string numero_turnos = PQgetvalue(res, 0, 0);

        query = R"(SELECT DISTINCT ON (id_student) * FROM view_student_assis WHERE id_subject = $1;)";
        PGresult *res_2 = PQexecParams(conn_gc, query.c_str(), 1, NULL, paramValue_1, NULL, NULL, 0);

        query = R"(SELECT total_turns FROM subjects WHERE id_subject = $1;)";
        PGresult *res_4 = PQexecParams(conn_gc, query.c_str(), 1, NULL, paramValue_1, NULL, NULL, 0);

        std::string total_turnos = PQgetvalue(res_4, 0, 0);

        query = R"(SELECT SUM(cantidad_turnos) AS asistencia FROM view_student_assis WHERE id_student = $1 AND id_subject = $2 AND assis GROUP BY assis;)";
        for (int i = 0; i < PQntuples(res_2); i++){
            const char *paramValue_2[2] = {PQgetvalue(res_2, i, 0) ,id_subject.c_str()};
            PGresult *res_3 = PQexecParams(conn_gc, query.c_str(), 2, NULL, paramValue_2, NULL, NULL, 0);

            std::cout << "Estudiante: " << PQgetvalue(res_2, i, 2) << " " << PQgetvalue(res_2, i, 3) << " " << PQgetvalue(res_2, i, 4) << std::endl;
            std::cout << "Asistencia " << PQgetvalue(res_3, 0, 0) << "/" << numero_turnos << " total de turnos -- " << total_turnos << std::endl;

            float asistencias_student = std::stof(PQgetvalue(res_3, 0, 0));
            float total_turn = std::stof(numero_turnos); 

            std::cout << "Porcentaje de asistencia " << (asistencias_student / total_turn) * 100 << "%" << std::endl;
            std::cout << "\n";
        }
        
        PQclear(res_2);
        PQclear(res);        
    }
}
