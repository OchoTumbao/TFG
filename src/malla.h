// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   void draw();
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   protected:
   void rellenar_colores();

 GLuint CrearVBO(GLuint tipo_vbo , GLuint tamanio_bytes ,
GLvoid * puntero_ram);
   GLuint id_vbov=0;
   GLuint id_vbof=0;
   GLuint id_vbocf=0;
   Tupla3f c_fill=Tupla3f(1.0,0.0,1.0);
   std::vector<Tupla3f> color_fill ;
   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
