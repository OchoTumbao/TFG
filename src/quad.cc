#include "quad.h"

Quad::Quad(unsigned int colorTextureid){
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    colorTextureID=colorTextureid;
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Quad::draw(){
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, colorTextureID);	// use the color attachment texture as the texture of the quad plane
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
}