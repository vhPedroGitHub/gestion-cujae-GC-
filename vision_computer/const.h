#include<iostream>
#include<string>

using namespace std;

// Constantes

// directorios
const string FD_MODELPATH = "../sources/models/face_detection_yunet_2023mar.onnx"; 
const string FR_MODELPATH = "../sources/models/face_recognition_sface_2021dec.onnx";

// parametros del modelo
const float SCORE_THRESHOLD = static_cast<float>(0.7); 
const float NMS_THRESHOLD = static_cast<float>(0.3);
const int TOP_K = 5000;

// tamano por defecto de las imagenes
const int MAX_HEIGHT = 320;
const int MAX_WIDTH = 320;

// limites para el reconocimiento facial
const double cosine_similar_thresh = 0.363;
const double l2norm_similar_thresh = 1.128;
