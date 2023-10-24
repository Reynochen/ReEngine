#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec2 vTexcoord;
in vec3 vNormal;

in float fragTime;

uniform sampler2D Texture;
uniform vec3 viewPos;

void main()
{
    vec3 ambient = vec3(0.5, 0.5, 0.5); //Grey

    // Diffuse light
    // lightColor/lightSource, normal
    vec3 normal = normalize(vNormal);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightSource = vec3(1.0, 1.0, 1.0);
    float diffuseStrength = max(0.0, dot(lightSource, normal));
    vec3 diffuse = diffuseStrength * lightColor;

    // Specular light
    vec3 cameraSource = viewPos;
    vec3 viewSource = normalize(cameraSource);
    vec3 reflectSource = normalize(reflect(-lightSource, normal));
    float specularStrength = max(0.0, dot(viewSource, reflectSource));
    specularStrength = pow(specularStrength, 32.0);
    vec3 specular = specularStrength * lightColor;

    // Lighting
    vec3 lighting = vec3(0.0, 0.0, 0.0);
    lighting = ambient * 0.0 + diffuse * 0.8 + specular * 0.8;

    vec3 modelColor = vec3(0.75, 0.75, 0.75);
    vec3 color = modelColor * lighting;

    FragColor = texture(Texture, vTexcoord) * vec4(color, 1.0);
}