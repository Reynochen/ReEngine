#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec2 vTexcoord;
in vec3 vNormal;

in float fragTime;

uniform sampler2D Texture;
uniform vec3 viewPos;

uniform vec3 lightDir; //For future
uniform vec3 lightPos;

void main()
{
    // lightColor/lightSource, normal
    vec3 normal = normalize(vNormal);
    vec3 lightColor = vec3(0.8, 0.8, 0.8);
    vec3 lightSource = vec3(1.0, 1.0, 1.0);

    //Diffuse
    float intensityDif = dot(lightSource, normal);

    vec3 diffuse = vec3(0.2, 0.2, 0.2);
    if (intensityDif > 0.95)
        diffuse = vec3(0.9, 0.9, 0.9);
    else if (intensityDif > 0.4)
        diffuse = vec3(0.4, 0.4, 0.4);

    // Specular light
    vec3 cameraSource = viewPos;
    vec3 viewSource = normalize(cameraSource);
    float intensitySpecular = normalize(dot(lightSource, normal));
    
    vec3 specular = vec3(0.0, 0.0, 0.0);

    if (intensityDif > 1.6)
        specular = intensitySpecular * lightColor;

    vec3 color = diffuse;

    FragColor = texture(Texture, vTexcoord) * vec4(color, 1.0);
}