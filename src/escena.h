#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "objply.h"
#include "camara.h"
#include "shader.h"
#include "framebuffer.h"
#include "quad.h"
#include "algoritmo.h"
#include "ShaderUBO.h"
#include "ShaderSSBO.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:

   bool estadoRaton = false;

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;
   GLfloat * depthdata;
   GLubyte * colordata;
   glm::mat4 model;
   glm::mat4 view;
   glm::mat4 projection;
   glm::mat4 mvp;
   int indice_textura_resultados;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   Camara * camara;
   menu modoMenu=NADA;
   Shader* shader;
   Shader* result_shader;
   Shader* render_shader;
   ShaderSSBO* result_shader_ssbo;
   FBO* framebuffer1;
   // Objetos de la escena
   Ejes ejes;
   ObjPLY * Escultura=nullptr;
   float xant = 0, yant = 0;
   Quad * renderQuad=nullptr;
   Algoritmo * algoritmo=nullptr;
   float dvalue=0.0f;

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void ratonMovido ( int x, int y );
   void clickRaton( int boton, int estado, int x, int y);
   void updatemvp(Shader * shader);
   float* getMVP(float* mv, float* p);
   void primitivas_resultados();

};
#endif
