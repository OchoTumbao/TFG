#version 410

uniform int primitive_num;

out vec4 outCol;
in vec4 v_color;

void main(){
    outCol = v_color;
}