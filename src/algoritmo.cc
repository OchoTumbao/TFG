#include "algoritmo.h"

Algoritmo::Algoritmo(int width, int heigth,float far, float near){
    this->width=width;
    this->heigth=heigth;
    this->far=far;
    this->near=near;
}

void Algoritmo::setValues(GLubyte * color, GLfloat * depth){
    this->colors=color;
    this->depth=depth;
    bool newVisitados[width*heigth]= {false};
    this->visitados=newVisitados;
    resetvisitados();
    bool newResultados[width*heigth]= { false };
    this->resultados=newResultados;
    for(int i=0;i<width*heigth;i++){
        resultados[i]=false;
    }
}

void Algoritmo::resetvisitados(){
        for(int i=0;i<width*heigth;i++){
        visitados[i]=false;
    }
    

}

void Algoritmo::iniciaAlgoritmo(int x_ini, int y_ini){
    actual=glm::vec2(x_ini,y_ini);
    mayor_profundidad=0.0;
    estado=FASE1;
}

float Algoritmo::getDepth(int x,int y){
    //return (float) depth[x*heigth+y];
    //return (float) depth[y*width+x];
    return (float) depth[(heigth-y)*width+x];
}

int Algoritmo::getColor(int x, int y){
    //return (int) colors[x*heigth+y];
    //return (int) colors[y*width+x];
    return (int) colors[(heigth-y)*width+x];
}

bool Algoritmo::getVisitado(int x,int y){
    //return visitados[x*heigth+y];
    //return visitados[y*width+x];
    return visitados[(heigth-y)*width+x];
}

void Algoritmo::setVisitado(int x,int y, bool value){
    //visitados[x*heigth+y]=value;
    //visitados[y*width+x]=value;
    visitados[(heigth-y)*width+x]=value;
}

void Algoritmo::setResultado(int x,int y, bool value){
    //resultados[x*heigth+y]=value;
    //resultados[y*width+x]=value;
    resultados[(heigth-y)*width+x]=value;
}

glm::vec2 Algoritmo::generaMejorVecino(){
    float profundidad_actual=getDepth(actual[0],actual[1]);
    glm::vec2 mejorvecino(actual[0],actual[1]);
    float depth_comprobada;
    for(int y=actual[1]-1;y<=actual[1]+1;y++){
        if(y>=0 && y<heigth){
            for(int x=actual[0]-1;x<=actual[0]+1;x++){
                if(x>=0 && x<width){
                if(getVisitado(x,y)==false){
                depth_comprobada=getDepth(x,y);
                if(depth_comprobada<profundidad_actual){
                    mejorvecino[0]=x;
                    mejorvecino[1]=y;
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
    //std::cout << actual.x << "," << actual.y << std::endl;
    if(mejorVecino==actual){
        resetvisitados();
        expand.push(actual);
        std::cout << "Nodo final " << actual[0] << "," << actual[1] << std::endl;
        estado=FASE2;
        setResultado(mejorVecino[0],mejorVecino[1],true);
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
            /*std::cout << "lista de resultados" << std::endl;
            for(int i=0;i<width*heigth;i++){
                if(resultados[i]==true){
                    std::cout << "valor de i " << i << std::endl;
                    std::cout << ":" << i%width << "," << i/width << ":" << std::endl;
                }
            }*/
        }
    } 
}

void Algoritmo::expandeNodo(glm::vec2 nodo){
        float depth_nodo=getDepth(nodo[0],nodo[1]);
        //std::cout << "Visitando "<< nodo[0] << "," << nodo[1] << std::endl;
        float depth_comprobada;
        if(depth_nodo>mayor_profundidad){
            std::cout << "Nodo con mayor profundidad" << getTrueZvalue(nodo[0],nodo[1]) << std::endl;
            mayor_profundidad=getTrueZvalue(nodo[0],nodo[1]);
        }
        for(int y=nodo[1]-1;y<=nodo[1]+1;y++){
        if(y>=0 && y<heigth){
            for(int x=nodo[0]-1;x<=nodo[0]+1;x++){
                if(x>=0 && x<width){
                if(getVisitado(x,y)==false){
                    setVisitado(x,y,true);
                depth_comprobada=getDepth(x,y);
                if(depth_comprobada>depth_nodo){
                    //std::cout << "Forma parte de la convexidad " << x << "," << y << std::endl;
                    setResultado(x,y,true);
                    expand.push(glm::vec2(x,y));
                    }else{
                        //setResultado(x,y,false);
                    }
                } else{
                    //setResultado(x,y,false);
                } 
                }
                
            }
        }
    }
}

void Algoritmo::run(){
    std::cout << "Nodo inicial " << actual[0] << "," << actual[1] << std::endl;
    mayor_profundidad=0.0;
    while(estado!=FINALIZADO){
        Nextstep();
    }
    //std::cout << "ALGORITMO ACABADO" << std::endl;
}


bool Algoritmo::isOver(){
    return estado==FINALIZADO;
}

float Algoritmo::getTrueZvalue(int x, int y){
    float z_b=getDepth(x,y);
    float z_e = 2*far*near / (far + near + (far - near)*(2*z_b -1));
    return z_e;
}

