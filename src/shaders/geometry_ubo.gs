#version 430 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec4 plane;
layout (std140, binding=2) uniform primitivas_block{
int primitivas_afectadas;
int primitivas[10000];
};

uniform float d;
bool afectada=false;
uniform mat4 mvp;


vec4 nuevoPunto(vec4 Punto){
    vec4 PuntoOriginal=inverse(mvp)*Punto;
    float lambda=(((plane.x*PuntoOriginal.x)+(plane.y*PuntoOriginal.y)+(plane.z*PuntoOriginal.z)+plane.w)/(pow(plane.x,2)+pow(plane.y,2)+pow(plane.z,2)))*-1;
    vec4 Q=vec4(PuntoOriginal.x+(plane.x*lambda),PuntoOriginal.y+(plane.y*lambda),PuntoOriginal.z+(plane.z*lambda),1.0);
    vec4 p_res=((PuntoOriginal+1.0*(PuntoOriginal-Q)));
    vec4 res=mvp*p_res;
    return res;
}

void main(){
        gl_PrimitiveID=gl_PrimitiveIDIn;
        for(int i=0; i<primitivas_afectadas;i++){
        if(gl_PrimitiveIDIn==primitivas[i]){
            afectada=true;
        }
    }
    if(afectada==true){
    gl_Position =nuevoPunto(gl_in[0].gl_Position);
    EmitVertex();
    gl_Position =nuevoPunto(gl_in[1].gl_Position);
    EmitVertex();
    gl_Position =nuevoPunto(gl_in[2].gl_Position);
    EmitVertex();
    EndPrimitive();
    } else{
    gl_Position =gl_in[0].gl_Position;
    EmitVertex();
    gl_Position =gl_in[1].gl_Position;
    EmitVertex();
    gl_Position =gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();
    }
}