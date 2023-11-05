#ifndef ENGINE_ENTITY
#define ENGINE_ENTITY

#include <glm/glm.hpp>

class Model;
class Collision;
class Shader;
class Texture;

class Entity {
    Model* model = nullptr;
    Collision* collision = nullptr;
    Texture* texture = nullptr;

public:
    glm::vec3 position, originPos, rotation, scale;

    Entity(glm::vec3 position, Model* model, const char* texturePath);
    ~Entity();

    void render(Shader* shader);

};

#endif