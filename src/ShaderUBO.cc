#include "ShaderUBO.h"

ShaderUBO::ShaderUBO(const char* vertexPath, const char* geometryPath, const char* fragmentPath):Shader(vertexPath, geometryPath,fragmentPath){

    //Creamos UBO
    glGenBuffers(1,&uboID);
    glBindBuffer(GL_UNIFORM_BUFFER,uboID);
    glBufferData(GL_UNIFORM_BUFFER,sizeof(uboData),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboID); 
}

void ShaderUBO::updateUBOData(std::vector<int> primitivas){
    uboData.primitivas_afectadas=primitivas.size();
    for (int i=0;i<primitivas.size();i++){
        uboData.primitivas[i]=primitivas[i];
    }
}


void ShaderUBO::sendUBOData(){
    glBindBuffer(GL_UNIFORM_BUFFER,uboID);
    glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(uboData.primitivas_afectadas),&uboData.primitivas_afectadas);
    glBufferSubData(GL_UNIFORM_BUFFER,sizeof(uboData.primitivas_afectadas),sizeof(uboData.primitivas),&uboData.primitivas[0]);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    
}