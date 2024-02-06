#ifndef ENTMANAGER
#define ENTMANAGER

#include <string>
#include <glm/glm.hpp>

class Entity;
class Shader;
class Model;
class Camera;

class ENTController {
    Entity** entities = nullptr;
    Model** models = nullptr;

    int entityCount;
    int modelsCount;

    void loadModels(std::string pathToModels);

public:
    ENTController();
    ~ENTController();

    Entity* getEntity(int id);

    void renderEntities(Shader &shader, Camera &camera);

    int addEntity(glm::vec3 position, const char* modelPath = nullptr, const char* texPath = "");
    void removeEntity();

};

#endif