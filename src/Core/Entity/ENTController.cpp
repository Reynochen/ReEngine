#include "Entity.hpp"
#include "ENTController.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include <filesystem>

#include <vector>

#include "Model.hpp"
#include "Entity.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

ENTController::ENTController() 
{
    modelsCount = 0;
    entityCount = 0;

    loadModels("res/models/");
}

void ENTController::loadModels(std::string pathToModels)
{    
    namespace fs = std::filesystem;

    fs::recursive_directory_iterator iterator(pathToModels);
    
    for(decltype(iterator) end; iterator != end; ++iterator) { //Check all folder in Models
        if(iterator.depth()>0) iterator.disable_recursion_pending();

        if (iterator->is_directory()) continue;
        std::string filePathStr = iterator->path().string();
        std::string formatFile = filePathStr.erase(0, filePathStr.find_first_of(".")+1).c_str();

        //Load obj files
        if (formatFile != "obj") continue;

        std::string modelPathStr = iterator->path().string();
        std::string modelName = modelPathStr.erase(0, 11);
        if(modelName.find_first_of("\\") == std::string::npos) continue;
        modelName = modelName.erase(modelName.find_first_of("\\"), modelName.length()).c_str();

        Model** modelsBuf = models;

        modelsCount++;
        models = new Model*[modelsCount];

        for (int i = 0; i < modelsCount-1; i++)
        {
            models[i] = modelsBuf[i];
        }
        if (modelsCount-1) delete[] modelsBuf;

        models[modelsCount-1] = new Model(glm::vec3(0.f), "", "", iterator->path().string().c_str(), modelName.c_str());      
    }
}

int ENTController::addEntity(glm::vec3 position, const char* modelName, const char* texPath) 
{
    Entity** entityBuf = entities;                
    int modelID = -1;

    for(int i = 0; i < modelsCount; i++) 
    {
        if(models[i]->getModelName() != modelName) continue;
        modelID = i;
        break;
    }

    std::string emptyName = "";
    if(modelName == emptyName && modelsCount > 0) {
        modelID = 0;
    }

    if(modelID == -1) 
    {
        std::cerr << "ERROR::CREATE_ENTITY::Dont found model: " << modelName << '\n'; 
        return -1;
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
    return 0;
}

void ENTController::renderEntities(Shader &shader, Camera &camera) 
{
    shader.use();
    camera.update();
    shader.setFloat("time", (float)glfwGetTime());
    shader.setVec3("viewPos", camera.Position);

    for (int i = 0; i < entityCount; i++) {
        entities[i]->render(&shader);
    }
}

Entity* ENTController::getEntity(int id) 
{
    if(id < entityCount && id >= 0)
        return entities[id];
    else
        return nullptr;
}

void ENTController::removeEntity()
{
    if(entityCount-1 < 0) return;

    delete entities[entityCount-1];
    entityCount--;
}

ENTController::~ENTController() 
{
    // delete[] models;
    // delete[] entities;
}