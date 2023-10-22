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
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void initModel();
    void updateUniforms(Shader* shader);

public:
    Model(glm::vec3 position, Texture* textureDiffuse, Texture* textureSpecular, const char* modelPath);
    ~Model();

    void render(Shader* shader);

};

#endif