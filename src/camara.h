#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

enum camaras {ORTOGONAL, PERSPECTIVA};

class Camara
{
private:

    glm::vec3 eye;
    glm::vec3 at;
    glm::vec3 up;

    double buff;

    int tipo; //ORTOGONAL o Perspectiva
    float left, right, bottom, top, near, far; //o bien aspect, fov, near, far
    float leftz, rightz, bottomz, topz; //o bien aspect, fov, near, far
    float factor_zoom = 1;

    bool locked = false;

    glm::vec3 rotarEjeX(glm::vec3 punto, float radianes) ; //Rota en el eje X un punto
    glm::vec3 rotarEjeY(glm::vec3 punto, float radianes) ; //Rota en el eje Y un punto
    glm::vec3 rotarEjeZ(glm::vec3 punto, float radianes) ; //Rota en el eje Z un punto
    glm::vec3 rotarEje(glm::vec3 punto, float radianes, int eje) ; //Rota en un eje un punto
    glm::vec3 alinearEjes(glm::vec3 p);
    glm::vec3 desalinearEjes(glm::vec3 p);
    glm::vec3 normalizar(glm::vec3 t);
    void updateZoom();

    int id_obj_point = -1;

public:

    Camara(int tipo_, glm::vec3 eye_, glm::vec3 at_);
    void mover(float x, float y, float z);
    void avanzar(bool dir);
    void retroceder(bool dir);
    void zoom(float factor);
    void actualizarRatio(float left_, float right_, float bottom_, float top_, float near_, float far_);
    glm::mat4 setObserver();
    glm::mat4 setProyeccion();

    void girar(float x, float y);
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    glm::vec3 devolverDireccion();
    int getTipo();
    void setPoint(int id);
    int getPoint();

    void lock(glm::vec3 point);
    void unlock();
    bool isLocked();
    
} ;

#endif