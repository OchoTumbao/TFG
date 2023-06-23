#include "camara.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

    Camara::Camara(int tipo_, glm::vec3 eye_, glm::vec3 at_)
    {
        up = {0, 1, 0};
        at = glm::vec3(at_[0],at_[1],at_[2]);
        eye = glm::vec3(eye_[0],eye_[1],eye_[2]);

        near = 50.0;
        far = 2000.0;

        tipo = tipo_;
    }

    void Camara::actualizarRatio(float left_, float right_, float bottom_, float top_, float near_, float far_)
    {
        if (left_ != 0.0)
            left = left_;

        if (right_ != 0.0)
            right = right_;

        if (bottom_ != 0.0)
            bottom = bottom_;

        if (top_ != 0.0)
            top = top_;

        if (near_ != 0.0)
            near = near_;

        if (far_ != 0.0)
            far = far_;
    }

    void Camara::rotarXExaminar(float angle)
    {
        glm::vec3 p = eye-at;
        p = alinearEjes(p);
        p = rotarEjeX(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
        eye = at + p;
    }

    void Camara::rotarYExaminar(float angle)
    {
        eye = at + rotarEjeY(eye-at, angle);
    }

    void Camara::rotarZExaminar(float angle)
    {
        glm::vec3 p = eye-at;
        p = alinearEjes(p);
        p = rotarEjeZ(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
        eye = at + p;
    }

    void Camara::rotarXFirstPerson(float angle)
    {

        glm::vec3 p = at-eye;
        p = alinearEjes(p);
        p = rotarEjeX(p, angle);
        p = desalinearEjes(p);
        //if ( at(0)*p(0) >= 0 )
            at = eye + p;
    }

    void Camara::rotarYFirstPerson(float angle)
    {
        at = eye + rotarEjeY(at-eye, angle);
    }

    void Camara::rotarZFirstPerson(float angle)
    {
        glm::vec3 p = at-eye;
        p = alinearEjes(p);
        p = rotarEjeZ(p, angle);
        p = desalinearEjes(p);
        at = eye + p;
    }

    void Camara::mover(float x, float y, float z)
    {
        glm::vec3 vector = at - eye;
        eye = {x, y, z};
        if (!locked)
            at = eye + vector;
    }

    void Camara::avanzar(bool dir)
    {
        glm::vec3 vector = devolverDireccion();

        if (!dir)
            vector = glm::vec3(vector[0]*-1,vector[1]*-1,vector[2]*-1);

        eye = eye + vector;
    
        if (!locked)
            at = at + vector;
    }

    void Camara::retroceder(bool dir)
    {
        glm::vec3 vector = devolverDireccion();
        if (!dir){
            vector = glm::vec3(vector[0]*-1,vector[1]*-1,vector[2]*-1);
        }

        eye = eye - vector;
    
        if (!locked){
            at = at - vector;
        }
    }

    glm::vec3 Camara::devolverDireccion()
    {
        return 0.5f*normalizar(at - eye);
    }

    void Camara::zoom(float factor)
    {
        factor_zoom *= factor;

        if (factor_zoom > 1.2)
            factor_zoom = 1.2;
    }

    glm::mat4 Camara::setObserver()
    {
        return glm::lookAt(eye,at,up);
    }

    glm::mat4 Camara::setProyeccion()
    {
        if (tipo == PERSPECTIVA)
        {
            return glm::frustum(left*factor_zoom, right*factor_zoom, bottom*factor_zoom, top*factor_zoom, near, far);
        }
    }

    glm::vec3 Camara::rotarEjeX(glm::vec3 p, float radianes)
    {
        glm::vec3 salida;

        salida[0] = p[0];
        salida[1] = cos(radianes)*p[1] - sin(radianes)*p[2];
        salida[2] = sin(radianes)*p[1] + cos(radianes)*p[2];

        return salida;
    }

    glm::vec3 Camara::rotarEjeY(glm::vec3 p, float radianes)
    {
        glm::vec3 salida;

        salida[0] = cos(radianes)*p[0] + sin(radianes)*p[2];
        salida[1] = p[1];
        salida[2] = -sin(radianes)*p[0] + cos(radianes)*p[2];

        return salida;
    }

    glm::vec3 Camara::rotarEjeZ(glm::vec3 p, float radianes)
    {
        glm::vec3 salida;

        salida[0] = cos(radianes)*p[0] - sin(radianes)*p[1];
        salida[1] = sin(radianes)*p[0] + cos(radianes)*p[1];
        salida[2] = p[2];

        return salida;
    }

    void Camara::girar(float x, float y)
    {
        if (locked)
        {
            rotarYExaminar(-x);
            rotarXExaminar(-y);
        }

        else
        {
            rotarYFirstPerson(-x);
            rotarXFirstPerson(y);
        }
    }

    glm::vec3 Camara::alinearEjes(glm::vec3 p)
    {

        glm::vec3 z = {0, 0, 1};
        buff = acosf((p[0]*z[0] + p[2]*z[2]) / ( sqrt(p[0]*p[0]+p[2]*p[2]) * sqrt(z[0]*z[0]+z[2]*z[2]) ));
        
        if (p[0] < 0)
        {
            p = rotarEjeY(p, buff);
            buff = -buff;
        }
        else
            p = rotarEjeY(p, -buff);

        return p;
    }

    glm::vec3 Camara::desalinearEjes(glm::vec3 p)
    {
        p = rotarEjeY(p, buff);

        return p;
    }

    glm::vec3 Camara::normalizar(glm::vec3 t)
    {
        float modulo = sqrt(pow(t[0],2) + pow(t[1],2) + pow(t[2],2));
        return t*(1/modulo);
    }

    void Camara::setPoint(int id)
    {
        id_obj_point = id;
    }

    int Camara::getPoint()
    {
        return id_obj_point;
    }

    void Camara::lock(glm::vec3 point)
    {
        locked = true;
        at = point;
    }

    void Camara::unlock()
    {
        locked = false;
    }

    bool Camara::isLocked()
    {
        return locked;
    }
