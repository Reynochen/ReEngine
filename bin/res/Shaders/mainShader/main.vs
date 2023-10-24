#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexcoord;
layout (location = 3) in vec3 vertexColor;

out vec3 vPos;
out vec3 vNormal;
out vec2 vTexcoord;
out vec3 vColor;

out float fragTime;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

void main()
{
    fragTime = time;

    vPos = vertexPos;
    vNormal = transpose(inverse(mat3(model))) * vertexNormal;
    vTexcoord = vec2(vertexTexcoord.x, vertexTexcoord.y * -1.f);
    vColor = vertexColor;

    // vPos.x += sin(time+vPos.x*8)/8;
    // vPos.y += sin(time + vPos.x*8)/8;
    // vPos.z += sin(time + vPos.y*8)/8;

    gl_Position = projection * view * model * vec4(vPos, 1.0);
}