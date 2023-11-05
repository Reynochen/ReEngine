#include "Entity.hpp"
#include "ENTManager.hpp"

#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <filesystem>

#include <vector>

#include "Model.hpp"
#include "Entity.hpp"

ENTManager::ENTManager() 
{
    loadModels("res/models/");

}

void ENTManager::loadModels(std::string pathToModels)
{    
    namespace fs = std::filesystem;
    modelsCount = 0;
    entityCount = 0;

    for(auto& folderPath : fs::recursive_directory_iterator(pathToModels)) { //Check all folder in Models
        if (!folderPath.is_directory()) continue;
            
        for(auto& filePath : fs::recursive_directory_iterator(folderPath.path())) { //Check file in models folder
            if (filePath.is_directory()) continue;

            std::string filePathStr = filePath.path().string();
            std::string formatFile = filePathStr.erase(0, filePathStr.find_first_of(".")+1).c_str();

            if (formatFile == "obj") { //Load obj files
                Model** modelsBuf = models;

                modelsCount++;
                models = new Model*[modelsCount];

                for (int i = 0; i < modelsCount-1; i++)
                {
                    models[i] = modelsBuf[i];
                }
                if (modelsCount-1) delete[] modelsBuf;
                
                models[modelsCount-1] = new Model(glm::vec3(0.f), "res/white.jpg", "res/white.jpg", filePath.path().string().c_str());
                break;
            }
        }
    }
}

void ENTManager::addEntity(glm::vec3 position, const char* modelName, const char* texPath) 
{
    Entity** entityBuf = entities;                
    int modelID = -1;

    for(int model = 0; model < modelsCount; model++) 
    {
        if(models[model]->getModelPath() != modelName) continue;
        modelID = model;
        break;
    }

    if(modelID == -1) 
    {
        std::cout << "ERROR::CREATE_ENTITY::NOT_FOUND_MODEL\n"; 
        return;
    }

    entityCount++;
    entities = new Entity*[entityCount];

    for (int i = 0; i < entityCount-1; i++) 
    {
        entities[i] = entityBuf[i];
    }

    delete[] entityBuf;
    entities[entityCount-1] = new Entity(position, models[modelID], texPath);
    std::cout << entityCount << '\n';
}

void ENTManager::renderEntities(Shader &shader) 
{
    for (int i = 0; i < entityCount; i++) {
        entities[i]->render(&shader);
    }
}

Entity* ENTManager::getEntity(int id) 
{
    if(id < entityCount && id >= 0)
        return entities[id];
    else
        return nullptr;
}

void ENTManager::removeEntity()
{
    if(entityCount-1 < 0) return;

    delete entities[entityCount-1];
    entityCount--;
}

ENTManager::~ENTManager() 
{
    // delete[] models;
    // delete[] entities;
}