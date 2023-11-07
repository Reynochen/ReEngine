#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec2 vTexcoord;
in vec4 vColor;

in float fragTime;

uniform sampler2D Texture;
uniform vec3 viewPos;

void main()
{
    FragColor = texture(Texture, vTexcoord) * vec4(vColor);
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}