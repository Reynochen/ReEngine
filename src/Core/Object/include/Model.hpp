#ifndef ENGINE_MODEL
#define ENGINE_MODEL

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>

class Mesh;
class Shader;
class Texture;
struct Vertex;

class Model {
    Texture* textureDiffuse;
    Texture* textureSpecular;
    std::vector<Mesh*> meshes;
    
    glm::mat4 ModelMatrix;

    void initModel();
    void initModelMatrix();
    void updateUniforms(Shader* shader);

public:
    glm::vec3 position, rotation, scale;
    
    Model(glm::vec3 position, Texture* textureDiffuse, Texture* textureSpecular, const char* modelPath);
    ~Model();

    void render(Shader* shader);

};

#endif