#ifndef ENTMANAGER
#define ENTMANAGER

#include <vector>
#include <string>

class Entity;
class Shader;

class ENTManager {
    Entity** entities = nullptr;
    int entityCount;

    Model** models = nullptr;
    int modelCount;

    void loadModels(std::string pathToModels);

public:
    ENTManager();
    ~ENTManager();

    Entity* getEntity(int id);

    void renderEntities(Shader &shader);

    void addEntity(glm::vec3 position);
    void removeEntity();

};

#endif