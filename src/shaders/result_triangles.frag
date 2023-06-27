#version 410

uniform int primitive_num;
uniform int primitivas_afectadas;
uniform int primitivas[10000];

out vec4 outCol;

bool afectada=false;

vec4 base255(){
    float valor3=floor(gl_PrimitiveID/255);
    float resultado3=mod(gl_PrimitiveID,255);
    float valor2=floor(valor3/255);
    float resultado2=mod(valor3,255);
    float valor1=floor(valor2/255);
    float resultado1=mod(valor2,255);
    return vec4(resultado1/255,resultado2/255,resultado3/255,1.0);
}

void main()
{
    for(int i=0; i<primitivas_afectadas;i++){
        if(gl_PrimitiveID==primitivas[i]){
            afectada=true;
        }
    }
    if(afectada==true){
    outCol=vec4(0.0,0.0,1.0,1.0);
    }else{
	float color= 1.0f/primitive_num;
    outCol = vec4(gl_PrimitiveID*color,0.0,0.0,1.0);
    }

}