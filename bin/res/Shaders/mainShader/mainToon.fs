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
    vec3 reflectSource = normalize(reflect(-lightSource, normal));
    float specularStrength = max(0.0, dot(viewSource, reflectSource));
    specularStrength = pow(specularStrength, 32.0);
    vec3 specular = specularStrength * lightColor;

    vec3 color = diffuse + specular;

    FragColor = texture(Texture, vTexcoord) * vec4(color, 1.0);
}