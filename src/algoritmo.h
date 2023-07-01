#include "aux.h"
#include <queue>

enum Estado {FASE1,FASE2,FINALIZADO};

class Algoritmo{
    private:
    GLfloat* depth;
    GLubyte* colors;
    bool* visitados=nullptr;
    glm::vec2 actual;
    bool finished;
    Estado estado;
    std::queue<glm::vec2> expand;
    float far, near;
    
    public:
    Algoritmo(int width, int heigth,float far, float near);

    glm::vec2 generaMejorVecino();
    void resetvisitados();
    void Nextstep();
    void run();
    void setValues(GLubyte * color, GLfloat * depth);
    float getDepth(int x, int y);
    int getColor(int x, int y);
    bool getVisitado(int x, int y);
    void setVisitado(int x, int y, bool value);
    bool getResultado(int x, int y);
    void setResultado(int x, int y, bool value);
    void iniciaAlgoritmo(int x_ini, int y_ini);
    void expandeNodo(glm::vec2 nodo);
    void depura_resultados();
    bool isOver();
    float getTrueZvalue(int x, int y);
    float mayor_profundidad=0.0f;
    float z_inicial;
    bool* resultados=nullptr;
    int width;
    int heigth;
    
    
};