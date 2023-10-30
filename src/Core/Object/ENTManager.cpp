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
    modelCount = 0;
    entityCount = 0;

    for(auto& folderPath : fs::recursive_directory_iterator(pathToModels)) { //Check all folder in Models
        if (!folderPath.is_directory()) continue;
            
        for(auto& filePath : fs::recursive_directory_iterator(folderPath.path())) { //Check file in model folder
            if (filePath.is_directory()) continue;

            std::string filePathStr = filePath.path().string();
            std::string formatFile = filePathStr.erase(0, filePathStr.find_first_of(".")+1).c_str();

            if (formatFile == "obj") {
                Model** modelsBuf = models;

                modelCount++;
                models = new Model*[modelCount];

                for (int i = 0; i < modelCount-1; i++)
                {
                    models[i] = modelsBuf[i];
                }
                if (modelCount-1) delete[] modelsBuf;
                
                models[modelCount-1] = new Model(glm::vec3(0.f), "res/white.jpg", "res/white.jpg", filePath.path().string().c_str());
            }
        }
    }
}

void ENTManager::addEntity(glm::vec3 position) 
{
    Entity** entityBuf = entities;                
                
    entityCount++;
    entities = new Entity*[entityCount];

    for (int i = 0; i < entityCount-1; i++) 
    {
        entities[i] = entityBuf[i];
    }
    if (entityCount-1) delete[] entityBuf;

    entities[entityCount-1] = new Entity(position, models[0], "");
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

ENTManager::~ENTManager() 
{
    // delete[] entities;
    // delete[] models;
}