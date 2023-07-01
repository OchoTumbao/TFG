#ifndef SHADERSSBO_H
#define SHADERSSBO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "aux.h"
#include "shader.h"
#include <vector>

struct primitivas_ssbo{
    int primitivas_afectadas;
    std::vector<int> primitivas;
};

class ShaderSSBO :public Shader{
    private:
    unsigned int ssboID;
    primitivas_ssbo ssboData;
    public:
    ShaderSSBO(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
    void updateSSBOData(std::vector<int> primitivas);
    void sendSSBOData();
};

#endif