#ifndef SHADERVertexSSBO_H
#define SHADERVertexSSBO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "aux.h"
#include "shader.h"
#include <vector>

struct vertices_ssbo{
    int vertices_afectadas;
    std::vector<int> vertices;
};

class ShaderVertexSSBO :public Shader{
    private:
    unsigned int ssboID;
    vertices_ssbo ssboData;
    public:
    ShaderVertexSSBO(const char* vertexPath, const char* fragmentPath);
    void updateSSBOData(std::vector<int> vertices);
    void sendSSBOData();
};

#endif