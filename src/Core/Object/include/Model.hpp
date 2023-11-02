#ifndef ENGINE_MODEL
#define ENGINE_MODEL

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include <string>

class Mesh;
class Shader;
class Texture;
struct Vertex;

class Model {
    Texture* textureDiffuse;
    Texture* textureSpecular;
    std::vector<Mesh*> meshes;
    std::string modelPath;
    
    glm::mat4 ModelMatrix;

    void initModel();
    void initModelMatrix();
    void updateUniforms(Shader* shader);


public:
    glm::vec3 position, originPos, rotation, scale;
    
    Model(glm::vec3 position, const char* textureDiffusePath, const char* textureSpecularPath, const char* modelPath);
    ~Model();

    void render(Shader* shader);

    std::string getModelPath() {return modelPath;}
};

#endif