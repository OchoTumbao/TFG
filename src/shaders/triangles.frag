#version 410

uniform int primitive_num;

out vec4 outCol;


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
	float color= 1.0f/primitive_num;
    outCol = vec4(gl_PrimitiveID*color,gl_PrimitiveID*color,gl_PrimitiveID*color,1.0);

}
