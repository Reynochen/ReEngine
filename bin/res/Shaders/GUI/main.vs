#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexcoord;
layout (location = 3) in vec4 vertexColor;

out vec3 vPos;
out vec2 vTexcoord;
out vec4 vColor;

out float fragTime;

uniform mat4 model;

uniform float time;

void main()
{
    fragTime = time;

    vPos = vertexPos;
    vColor = vertexColor;
    vTexcoord = vertexTexcoord;

    // vPos.x += sin(time+vPos.x*80);
    // vPos.y += sin(time + vPos.x*8)/8;
    // vPos.z += sin(time + vPos.y*8)/8;

    gl_Position = model * vec4(vPos, 1.0);
}