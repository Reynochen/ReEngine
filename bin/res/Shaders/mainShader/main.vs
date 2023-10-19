#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexcoord;
layout (location = 3) in vec3 vertexColor;

out vec3 vPos;
out vec3 vNormal;
out vec2 vTexcoord;
out vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vPos = vertexPos;
    vNormal = vertexNormal;
    vTexcoord = vec2(vertexTexcoord.x, vertexTexcoord.y * -1.f);
    vColor = vertexColor;

    gl_Position = projection * view * model * vec4(vPos, 1.0);
}