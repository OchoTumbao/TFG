#include "ShadervertexSSBO.h"

ShaderVertexSSBO::ShaderVertexSSBO(const char* vertexPath, const char* fragmentPath):Shader(vertexPath,fragmentPath){

    //VertexCreamos ssbo
    glGenBuffers(1,&ssboID);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferData(GL_SHADER_STORAGE_BUFFER,sizeof(int)*10000,NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, ssboID); 
}

void ShaderVertexSSBO::updateSSBOData(std::vector<int> vertices){
    ssboData.vertices_afectadas=vertices.size();
    ssboData.vertices=vertices;
}


void ShaderVertexSSBO::sendSSBOData(){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboID);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,0,sizeof(ssboData.vertices_afectadas),&ssboData.vertices_afectadas);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER,sizeof(ssboData.vertices_afectadas),sizeof(int)*ssboData.vertices_afectadas,ssboData.vertices.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
    
}