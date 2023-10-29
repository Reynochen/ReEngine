#ifndef ENGINE_OBJECT
#define ENGINE_OBJECT

#include <glm/glm.hpp>

class Model;
class Collision;
class Shader;

class Object {
    Model* model = nullptr;
    Collision* collision = nullptr;

public:
    glm::vec3 position, originPos, rotation, scale;

    Object(glm::vec3 position, Model* model, const char* texturePath);
    ~Object();

    void render(Shader* shader);

};

#endif