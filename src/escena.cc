

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <iostream>
#include <vector>
#include <algorithm>

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 10.0;
    Back_plane        = 30.0;
    Observer_distance = 3*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
    Escultura= new ObjPLY("plys/Bearded_guy.ply");
    camara=new Camara(PERSPECTIVA,{0.0,0.0,20.0},{0.0,0.0,-1.0});

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   shader= new Shader("shaders/first_vertex.vert","shaders/triangles2.frag");
   render_shader= new Shader("shaders/render_shader.vert","shaders/render_depth.frag");
   result_shader= new Shader("shaders/first_vertex.vert","shaders/result_triangles2.frag");
   framebuffer1= new FBO(UI_window_width,UI_window_height);
   projection=camara->setProyeccion();
   view=camara->setObserver();
   model=glm::mat4(1.0f);
   model=glm::scale(model,glm::vec3(3.3,3.3,3.3));
   renderQuad=new Quad(framebuffer1->textureColorid);
   algoritmo=new Algoritmo(UI_window_width,UI_window_height);
	glViewport( 0, 0, UI_window_width, UI_window_height );
   
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{// Limpiar la pantalla

   mvp=projection*view*model;
   framebuffer1->use();
   glEnable(GL_DEPTH_TEST);
    if(framebuffer1->is_complete()){
   	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      if(!algoritmo->isOver()){
      shader->use(); 
      shader->setMatrix4Float("mvp",1,false,(float*)glm::value_ptr(mvp));
      shader->setInt("primitive_num",(int) Escultura->num_caras);
      
      Escultura->draw();
      framebuffer1->getColorData();
      framebuffer1->getDepthData();
      shader->stop();
      } else{
      result_shader->use(); 
      result_shader->setMatrix4Float("mvp",1,false,(float*)glm::value_ptr(mvp));
      result_shader->setInt("primitive_num",(int) Escultura->num_caras);
      Escultura->draw();
      framebuffer1->getColorData();
      framebuffer1->getDepthData();
      result_shader->stop();
      }

    }
   framebuffer1->stop();
    glDisable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    render_shader->use();
    render_shader->setInt("sceneTexture",framebuffer1->textureColorid);
    renderQuad->draw();
    render_shader->stop();
    

      //glEnable(GL_DEPTH_TEST);
   	/*glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  
      glClearColor( 1.0, 1.0, 1.0, 1.0 );
      shader->use(); 
      shader->setMatrix4Float("mvp",1,false,(float*)glm::value_ptr(mvp));
      shader->setInt("primitive_num",(int) Escultura->num_caras);
      Escultura->draw();
      shader->stop();*/

    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         camara->lock(glm::vec3(0.0,0.0,0.0));
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
       case '+':
         if(camara->isLocked()){
            camara->avanzar(true);
            view=camara->setObserver();
         }
       break;
       case '-':
         if(camara->isLocked()){
            camara->retroceder(true);
            view=camara->setObserver();
         }
       break;
         // COMPLETAR con los diferentes opciones de teclado
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camara -> girar(0.01, 0.0);//rotarYFirstPerson(0.1);
         view=camara->setObserver();
         break;
	   case GLUT_KEY_RIGHT:
         camara -> girar(-0.01, 0.0);
         view=camara->setObserver();
         break;
	   case GLUT_KEY_UP:
         camara -> girar(0.0, 0.01);
         view=camara->setObserver();
         break;
	   case GLUT_KEY_DOWN:
         camara -> girar(0.0, -0.01);
         view=camara->setObserver();
         break;
	}
}

	//std::cout << Observer_distance << std::endl;


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   camara -> actualizarRatio(-Width/2, Width/2, -Height/2, Height/2, Front_plane, Back_plane);
   projection=camara->setProyeccion();
   glViewport( 0, 0, newWidth, newHeight );
   framebuffer1->resize(newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************


void Escena::ratonMovido ( int x, int y )
{
   if (estadoRaton)
   {
      camara->girar((float)(x-xant)/100, (float)(y-yant)/100);

      xant = x;
      yant = y;
      view=camara->setObserver();
   }
}

void Escena::clickRaton( int boton, int estado, int x, int y)
{
   if ( boton == GLUT_RIGHT_BUTTON )
   {
      xant = x; yant = y;

      if (estado == GLUT_DOWN)
      {
         estadoRaton = true;
      }

      else
      {
         estadoRaton = false;
      }
   }

   else if( boton == GLUT_LEFT_BUTTON ){
      if(estado == GLUT_DOWN){
         algoritmo->iniciaAlgoritmo(x,y);
         algoritmo->setValues(framebuffer1->colordata,framebuffer1->depthdata);
         algoritmo->run();
         primitivas_resultados();
      }
   }
   else if ( boton == 4 )
   {
      camara->zoom(1.05);
      projection=camara->setProyeccion();
      view=camara->setObserver();
   }

   else if ( boton == 3)
   {
      camara->zoom(0.95);
      projection=camara->setProyeccion();
      view=camara->setObserver();
   }

}

void Escena::primitivas_resultados(){
   std::vector<int> primitivas;
   for(int i=0;i<algoritmo->width*algoritmo->heigth;i++){
      if(algoritmo->resultados[i]==true){
         std::cout << "Estoy mirando el pixel " << i/algoritmo->width << "," << i%algoritmo->width << std::endl;
         //std::cout << "Valor del array "<< algoritmo->resultados[i] << std::endl;
         int id_primitiva=(framebuffer1->colordata[i*3])*pow(255,2)+(framebuffer1->colordata[i*3+1])*255+framebuffer1->colordata[i*3+2];
         //int id_primitiva=framebuffer1->colordata[i*3]*(1.0f/Escultura->num_caras);
         //std::cout << "El valor de Rojo de este pixel es: " <<(float) framebuffer1->colordata[i*4] << std::endl;
         //std::cout << "Primitiva con ID " << id_primitiva << std::endl;
         if( std::find(primitivas.begin(),primitivas.end(),id_primitiva) == primitivas.end()){
         std::cout << "El valor de Rojo de este pixel es: " <<(float) framebuffer1->colordata[i*3] << std::endl;
         std::cout << "El valor de Verde de este pixel es: " <<(float) framebuffer1->colordata[i*3+1] << std::endl;
         std::cout << "El valor de Azul de este pixel es: " <<(float) framebuffer1->colordata[i*3+2] << std::endl;
         //std::cout << "El valor de Alpha de este pixel es: " <<(float) framebuffer1->colordata[i*4+3] << std::endl;
         std::cout << (255.0f/ Escultura->num_caras) << std::endl;
         std::cout << "Primitiva con ID " << id_primitiva << std::endl;
         std::cout << "Estoy mirando el pixel " << i/algoritmo->width << "," << i%algoritmo->width << std::endl;
         primitivas.push_back(id_primitiva);
         }
      }
   }
   std::cout << "Primitivas afectadas: " << primitivas.size() << std::endl;
   result_shader->use();
      result_shader->setvector1integer("primitivas",primitivas.size(),&primitivas[0]);
      result_shader->setInt("primitivas_afectadas",primitivas.size());
   result_shader->stop();
}



