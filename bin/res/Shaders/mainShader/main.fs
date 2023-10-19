#version 330 core
    
in vec3 vPos;
in vec3 vColor;
in vec2 vTexcoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0f);
}