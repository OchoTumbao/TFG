#include "ShaderSSBO.h"

ShaderSSBO::ShaderSSBO(const char* vertexPath, const char* geometryPath, const char* fragmentPath):Shader(vertexPath, geometryPath,fragmentPath){

    //Creamos ssbo
    glGenBuffers(1,&ssboID);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferData(GL_SHADER_STORAGE_BUFFER,sizeof(int)*10000,NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssboID); 
}

void ShaderSSBO::updateSSBOData(std::vector<int> primitivas){
    ssboData.primitivas_afectadas=primitivas.size();
    ssboData.primitivas=primitivas;
}


void ShaderSSBO::sendSSBOData(){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,0,sizeof(ssboData.primitivas_afectadas),&ssboData.primitivas_afectadas);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,sizeof(ssboData.primitivas_afectadas),sizeof(int)*ssboData.primitivas_afectadas,ssboData.primitivas.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    
}