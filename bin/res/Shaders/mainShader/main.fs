#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec3 vColor;
in vec2 vTexcoord;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, vTexcoord);
    // FragColor = vec4(vColor, 1.0f)
}