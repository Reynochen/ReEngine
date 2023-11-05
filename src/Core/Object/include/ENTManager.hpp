#ifndef ENTMANAGER
#define ENTMANAGER

#include <string>

class Entity;
class Shader;

class ENTManager {
    Entity** entities = nullptr;
    Model** models = nullptr;

    int entityCount;
    int modelsCount;

    void loadModels(std::string pathToModels);

public:
    ENTManager();
    ~ENTManager();

    Entity* getEntity(int id);

    void renderEntities(Shader &shader);

    void addEntity(glm::vec3 position, const char* modelPath = nullptr, const char* texPath = nullptr);
    void removeEntity();

};

#endif