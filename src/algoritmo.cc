#include "algoritmo.h"

Algoritmo::Algoritmo(int width, int heigth){
    this->width=width;
    this->heigth=heigth;

}

void Algoritmo::setValues(GLubyte * color, GLfloat * depth){
    this->colors=color;
    this->depth=depth;
    resetvisitados();
    bool newResultados[width*heigth]= { 0 };
    this->resultados=newResultados;
}

void Algoritmo::resetvisitados(){
    bool newvisitados[width*heigth] = { 0 };
    visitados=newvisitados;

}

void Algoritmo::iniciaAlgoritmo(int x_ini, int y_ini){
    actual=glm::vec2(y_ini,x_ini);
    estado=FASE1;
    resetvisitados();

}

float Algoritmo::getDepth(int x,int y){
    return (float) depth[y*width+x];
}

int Algoritmo::getColor(int x, int y){
    return (int) colors[y*width+x];
}

bool Algoritmo::getVisitado(int x,int y){
    return visitados[y*width+x];
}

void Algoritmo::setVisitado(int x,int y, bool value){
    visitados[y*width+x]=value;
}

void Algoritmo::setResultado(int x,int y, bool value){
    resultados[y*width+x]=value;
}

glm::vec2 Algoritmo::generaMejorVecino(){
    float profundidad_actual=getDepth(actual[1],actual[0]);
    glm::vec2 mejorvecino(actual[0],actual[1]);
    float depth_comprobada;
    for(int y=actual[0]-1;y<=actual[0]+1;y++){
        if(y>=0 && y<heigth){
            for(int x=actual[1]-1;x<=actual[1]+1;x++){
                if(x>=0 && x<width){
                if(getVisitado(x,y)==false){
                depth_comprobada=getDepth(x,y);
                if(depth_comprobada>profundidad_actual){
                    mejorvecino[0]=y;
                    mejorvecino[1]=x;
                    profundidad_actual=depth_comprobada;
                    }
                setVisitado(x,y,true);
                }
                }
                
            }
        }
    }
    return mejorvecino;

}

void Algoritmo::Nextstep(){
    if(estado==FASE1){
    glm::vec2 mejorVecino=generaMejorVecino();
    if(mejorVecino==actual){
        resetvisitados();
        expand.push(actual);
        estado=FASE2;
    } else{
        actual=mejorVecino;
    }
    }
    if(estado==FASE2){
        if(!expand.empty()){
            expandeNodo(expand.front());
            expand.pop();
        }
        else{
            estado=FINALIZADO;
        }
    } 
}

void Algoritmo::expandeNodo(glm::vec2 nodo){
        std::cout << "ME EJECUTO" << std::endl;
        float depth_nodo=getDepth(nodo[1],nodo[0]);
        float depth_comprobada;
        for(int y=nodo[0]-1;y<=nodo[0]+1;y++){
        if(y>=0 && y<heigth){
            for(int x=nodo[1]-1;x<=nodo[0]+1;x++){
                if(x>=0 && x<width){
                if(getVisitado(x,y)==false){
                depth_comprobada=getDepth(x,y);
                if(depth_comprobada<depth_nodo){
                    expand.push(glm::vec2(y,x));
                    }
                setVisitado(x,y,true);
                setResultado(x,y,true);
                }
                }
                
            }
        }
    }
}

void Algoritmo::run(){
    while(estado!=FINALIZADO){
        Nextstep();
    }
    std::cout << "ALGORITMO ACABADO" << std::endl;
}

void Algoritmo::setTexturaResultados(int* indiceTextura){
    glGenTextures(1,indiceTextura);
    glBindTexture(GL_TEXTURE_2D,indiceTextura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,texture_width , texture_height, 0, GL_RED, GL_INT, resultados[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
}

