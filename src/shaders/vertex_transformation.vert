#version 430 core
layout ( location = 0 ) in vec3 pos;

uniform vec4 plane;
layout (std430, binding=4) buffer vertices_block{
int vertices_afectadas;
int vertices[];
};

uniform float d;
bool afectada=false;
uniform mat4 mvp;
out vec4 v_color;
float color=0.0;


vec4 nuevoPunto(vec4 Punto){
    vec4 PuntoOriginal=Punto;
    vec4 nuevoplane=mvp*plane;
    float lambda=(((nuevoplane.x*PuntoOriginal.x)+(nuevoplane.y*PuntoOriginal.y)+(nuevoplane.z*PuntoOriginal.z)+nuevoplane.w)/(-1*(pow(nuevoplane.x,2)+pow(nuevoplane.y,2)+pow(nuevoplane.z,2))));
    vec4 Q=vec4(PuntoOriginal.x+(nuevoplane.x*lambda),PuntoOriginal.y+(nuevoplane.y*lambda),PuntoOriginal.z+(nuevoplane.z*lambda),PuntoOriginal.w+(nuevoplane.w*lambda));
    vec4 p_res=((PuntoOriginal+d*(PuntoOriginal-Q)));
    return p_res;
}

void main(){
        for(int i=0; i<vertices_afectadas;i++){
            color=mod(color+1.0,255.0);
        if(gl_VertexID==vertices[i]){
            afectada=true;
        }
        }
    if(afectada==true){
    gl_Position =nuevoPunto(mvp*vec4(pos,1.0));
    v_color = vec4(1.0,0.0,0.0,1.0);
    } else{
    gl_Position=mvp*vec4(pos,1.0);
    v_color = vec4(0.0,0.0,color/255.0,1.0);
    }
}