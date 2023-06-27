#include "framebuffer.h"

FBO::FBO(int window_width,int window_height){
    texture_height=window_height;
    texture_width=window_width;
    glGenFramebuffers(1,&fboid);
    glBindFramebuffer(GL_FRAMEBUFFER, fboid);
    glGenTextures(1,&textureColorid);
    glBindTexture(GL_TEXTURE_2D,textureColorid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,texture_width , texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,texture_width , texture_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorid, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGenTextures(1,&textureDepthid);
    glBindTexture(GL_TEXTURE_2D,textureDepthid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, texture_width,texture_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthid, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    int i=glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(i!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not OK, status=" << i << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

}

void FBO::use(){
    glBindFramebuffer(GL_FRAMEBUFFER, fboid);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorid, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthid, 0);
}

void FBO::stop(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

bool FBO::is_complete(){
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void FBO::getDepthData(){
    /*glBindTexture(GL_TEXTURE_2D,textureDepthid);
    glGetTexImage(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,GL_FLOAT,depthdata);
    std::cout << "Sr" << std::endl;
    std::cout << depthdata << std::endl;
    glBindTexture(GL_TEXTURE_2D,0);*/
    GLfloat * pixels = (GLfloat*) malloc(texture_width*texture_height*sizeof(GLfloat));
    glReadPixels(0,0,texture_width,texture_height,GL_DEPTH_COMPONENT,GL_FLOAT,pixels);
    depthdata=pixels;
    //std::cout << "Sr" << std::endl;
    //
}

void FBO::getColorData(){
    GLubyte * pixels= (GLubyte*) malloc(texture_width*texture_height*sizeof(GLfloat));
     glReadPixels(0,0,texture_width,texture_height,GL_RGB,GL_UNSIGNED_BYTE,pixels);
     //glReadPixels(0,0,texture_width,texture_height,GL_RGB,GL_FLOAT,pixels);
     colordata=pixels;
     /*glBindTexture(GL_TEXTURE_2D,textureColorid);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_UNSIGNED_BYTE,colordata);
     glBindTexture(GL_TEXTURE_2D,0);*/
}

void FBO::resize(int new_window_width, int new_window_height){
    glDeleteFramebuffers(1, &fboid);  
    texture_height=new_window_height;
    texture_width=new_window_width;
    glBindTexture(GL_TEXTURE_2D,textureColorid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,texture_width , texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorid, 0);
    glBindTexture(GL_TEXTURE_2D,textureDepthid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, texture_width,texture_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureDepthid, 0);
    glBindRenderbuffer(GL_RENDERBUFFER,rboid);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_STENCIL,texture_width,texture_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rboid);
}


