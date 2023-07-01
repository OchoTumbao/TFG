#ifndef SHADERUBO_H
#define SHADERUBO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "aux.h"
#include "shader.h"
#include <vector>

struct primitivas{
    int primitivas_afectadas;
    int primitivas[10000];
};

class ShaderUBO :public Shader{
    private:
    unsigned int uboID;
    primitivas uboData;
    public:
    ShaderUBO(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
    void updateUBOData(std::vector<int> primitivas);
    void sendUBOData();
};

#endif