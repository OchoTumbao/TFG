#ifndef FBO_H_INCLUDED
#define FBO_H_INCLUDED

#include "aux.h"

class FBO
{
    private:

        int texture_height;
        int texture_width;

    public:

        FBO(int window_width,int window_height);
        void use();
        void stop();
        bool is_complete();
        void getDepthData();
        void getColorData();
        void resize(int new_window_width,int new_window_height);
        unsigned int textureColorid;
        unsigned int textureDepthid;
        unsigned int fboid;
        unsigned int rboid;
        GLfloat * depthdata;
        GLubyte * colordata;
};

#endif