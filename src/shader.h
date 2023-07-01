#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "aux.h"

class Shader
{
    protected:
    unsigned int ID;
    public:
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
    void use();
    void stop();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMatrix4Float(const std::string &name, int amount, bool transpose, float* value) const;
    void setvector1integer(const std::string &name,int amount, int* value) const;
    void setvec4float(const std::string &name,glm::vec4 value) const;

};

#endif