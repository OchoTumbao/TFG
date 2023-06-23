#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "aux.h"

class Shader
{
    private:
    unsigned int ID;
    public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void stop();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMatrix4Float(const std::string &name, int amount, bool transpose, float* value) const;

};

#endif