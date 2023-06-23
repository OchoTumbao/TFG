#version 410
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

float near=50.0;
float far=2000.0;

float linearizeDepth(float depth){
    return (2.0f * near) / (far + near - depth * (far - near));
}

void main()
{ 
    vec4 depthdata=texture(screenTexture,TexCoords);
    float normalized_depth=linearizeDepth(depthdata.x);
    FragColor = texture(screenTexture,TexCoords);
}