#ifndef ENTMANAGER
#define ENTMANAGER

#include <string>

class Entity;
class Shader;
class Model;

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

    void renderEntities(Shader &shader);

    void addEntity(glm::vec3 position, const char* modelPath = nullptr, const char* texPath = nullptr);
    void removeEntity();

};

#endif