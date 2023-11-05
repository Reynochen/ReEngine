#include <iostream>

#include "Entity.hpp"
#include "Model.hpp"
#include "Texture.hpp"


Entity::Entity(glm::vec3 position, Model* model, const char* texturePath) {
    //Init Data
    rotation = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    originPos = glm::vec3(0.f);

    //Set Data
    this->position = position;
    this->model = model;
    
    if(texturePath != nullptr)
        this->texture = new Texture(texturePath, GL_TEXTURE_2D, 2);
    
}

Entity::~Entity() {
    // delete model;
    // delete collision;
    delete texture;
}

void Entity::render(Shader* shader) {
    if(model == nullptr) return;

    model->position = position;
    model->originPos = originPos;
    model->rotation = rotation;
    model->scale = scale;
    model->render(shader, texture);
}
