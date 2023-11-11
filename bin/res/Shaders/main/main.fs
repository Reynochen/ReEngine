#version 330 core
out vec4 FragColor;
    
in vec3 vPos;
in vec2 vTexcoord;
in vec3 vNormal;
in vec4 vColor;

in float fragTime;

uniform vec3 viewPos;

uniform vec3 lightDir; //For future

uniform sampler2D Texture;
uniform bool texEmpty;

void main()
{
    vec3 ambient = vec3(0.5, 0.5, 0.5); //Grey

    // lightColor/lightSource, normal
    vec3 normal = normalize(vNormal);
    vec3 lightColor = vec3(0.9, 0.9, 0.9);
    vec3 lightSource = vec3(1.0, 1.0, 1.0);

    // Diffuse light
    float diffuseStrength = max(0.0, dot(normalize(lightSource), normal));
    vec3 diffuse = diffuseStrength * lightColor;

    // Specular light
    vec3 cameraSource = viewPos;
    vec3 viewSource = normalize(cameraSource);
    vec3 reflectSource = normalize(reflect(-lightSource, normal));
    float specularStrength = max(0.0, dot(viewSource, reflectSource));
    specularStrength = pow(specularStrength, 32.0);
    vec3 specular = specularStrength * lightColor;

    // Lighting
    vec3 lighting = ambient * 0.4 + diffuse * 1.0 + specular * 0.6;

    vec3 modelColor = vec3(vColor.x, vColor.y, vColor.z);
    vec3 color = modelColor * lighting;

    float intensity = dot(lightSource, normal);

    FragColor = texEmpty ? vec4(color, vColor.w) : texture(Texture, vTexcoord) * vec4(color, vColor.w);   
}