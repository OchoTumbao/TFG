#version 430 core


layout (std430, binding=3) buffer primitivas_block{
int primitivas_afectadas;
int primitivas[];
};

out vec4 outCol;
bool afectada=false;

float prueba=0.0;
vec4 base255(){
    float valor3=floor(gl_PrimitiveID/255);
    float resultado3=mod(gl_PrimitiveID,255);
    float valor2=floor(valor3/255);
    float resultado2=mod(valor3,255);
    float valor1=floor(valor2/255);
    float resultado1=mod(valor2,255);
    return vec4(resultado1/255,resultado2/255,resultado3/255,1.0);
}

vec4 base255d(){
    float valor3=floor(gl_PrimitiveID/255);
    float resultado3=mod(gl_PrimitiveID,255);
    float valor2=floor(valor3/255);
    float resultado2=mod(valor3,255);
    float valor1=floor(valor2/255);
    float resultado1=mod(valor2,255);
    return vec4(resultado1/255*0.3,resultado2/255*0.3,resultado3/255*0.3,1.0);
}

void main()
{
    for(int i=0; i<primitivas_afectadas;i++){
        if(gl_PrimitiveID==primitivas[i]){
            afectada=true;
        }

    }
    if(afectada==true){
    outCol=base255d();
    }else{
    outCol=base255();
    }
    
}
