#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint Malla3D::CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes ,
GLvoid * puntero_ram )
{
GLuint id_vbo ; // resultado: identificador de VBO
glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador
glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador
// esta instrucción hace la transferencia de datos desde RAM hacia GPU
glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
return id_vbo ; // devolver el identificador resultado
}



// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)

   

   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
   }
   if(id_vbof==0){
      id_vbof=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*f.size()*sizeof(int),&f[0]);
   }
   if(id_vbocf==0){
      id_vbocf=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&color_fill[0]);
   }
   glBindBuffer(GL_ARRAY_BUFFER,id_vbocf);

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ARRAY_BUFFER,id_vbov);
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbof);
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::rellenar_colores(){
      for(int i=0;i<v.size();i++){
      color_fill.push_back(c_fill);
      }
}



