#version 410

uniform int primitive_num;

out vec4 outCol;


void main()
{
	float color= 1.0f/primitive_num;
    outCol = vec4(gl_PrimitiveID*color, gl_PrimitiveID*color, gl_PrimitiveID*color,1.0);
}