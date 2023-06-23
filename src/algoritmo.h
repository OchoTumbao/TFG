#include "aux.h"
#include <queue>

enum Estado {FASE1,FASE2,FINALIZADO};

class Algoritmo{
    private:
    int width;
    int heigth;
    GLfloat* depth;
    GLubyte* colors;
    bool* visitados=nullptr;
    bool* resultados=nullptr;
    glm::vec2 actual;
    bool finished;
    Estado estado;
    std::queue<glm::vec2> expand;
    
    public:
    Algoritmo(int width, int heigth);

    glm::vec2 generaMejorVecino();
    void resetvisitados();
    void Nextstep();
    void run();
    void setValues(GLubyte * color, GLfloat * depth);
    float getDepth(int x, int y);
    int getColor(int x, int y);
    bool getVisitado(int x, int y);
    void setVisitado(int x, int y, bool value);
    void setResultado(int x, int y, bool value);
    void iniciaAlgoritmo(int x_ini, int y_ini);
    void expandeNodo(glm::vec2 nodo);
    void setTexturaResultados(int* indiceTextura);
    
    
};