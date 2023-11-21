#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec2 vTexcoord;
in vec4 vColor;

in float fragTime;

uniform sampler2D Texture;
uniform vec3 viewPos;
uniform bool texEmpty;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, vTexcoord).r);
    FragColor = texEmpty ? vec4(vColor) : vec4(vColor) * sampled;

}