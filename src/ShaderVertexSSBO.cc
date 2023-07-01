#include "ShaderSSBO.h"

ShaderVertexSSBO::ShaderSSBO(const char* vertexPath, const char* geometryPath, const char* fragmentPath):Shader(vertexPath, geometryPath,fragmentPath){

    //VertexCreamos ssbo
    glGenBuffers(1,&ssboID);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferData(GL_SHADER_STORAGE_BUFFER,sizeof(int)*10000,NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssboID); 
}

void ShaderSSBO::updateSSBOData(std::vector<int> vertices){
    ssboDatVertexa.vertices_afectadas=vertices.size();
    ssboData.vertices=vertices;
}


void ShaderSSBO::sendSSBOData(){
    glBindBVertexuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,0,sizeof(ssboData.vertices_afectadas),&ssboData.vertices_afectadas);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,sizeof(ssboData.vertices_afectadas),sizeof(int)*ssboData.vertices_afectadas,ssboData.vertices.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    
}