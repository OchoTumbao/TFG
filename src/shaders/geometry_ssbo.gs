#version 430 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec4 plane;
layout (std430, binding=3) buffer primitivas_block{
int primitivas_afectadas;
int primitivas[];
};

uniform float d;
bool afectada=false;
uniform mat4 mvp;
bool z_concavo=false;


vec4 nuevoPunto(vec4 Punto){
    vec4 PuntoOriginal=Punto;
    vec4 nuevoplane=mvp*plane;
    float lambda=(((nuevoplane.x*PuntoOriginal.x)+(nuevoplane.y*PuntoOriginal.y)+(nuevoplane.z*PuntoOriginal.z)+nuevoplane.w)/(-1*(pow(nuevoplane.x,2)+pow(nuevoplane.y,2)+pow(nuevoplane.z,2))));
    vec4 Q=vec4(PuntoOriginal.x+(nuevoplane.x*lambda),PuntoOriginal.y+(nuevoplane.y*lambda),PuntoOriginal.z+(nuevoplane.z*lambda),PuntoOriginal.w+(nuevoplane.w*lambda));
    vec4 p_res=((PuntoOriginal+d*(PuntoOriginal-Q)));
    return p_res;
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