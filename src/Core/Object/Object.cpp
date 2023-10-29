#include <iostream>

#include "Object.hpp"
#include "Model.hpp"


Object::Object(glm::vec3 position, Model* model, const char* texturePath) {
    //Init Data
    rotation = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    originPos = glm::vec3(0.f);

    //Set Data
    this->position = position;

    this->model = model;
}

Object::~Object() {
    delete model;
    delete collision;
}

void Object::render(Shader* shader) {
    if(model == nullptr) return;
    
    model->position = position;
    model->originPos = originPos;
    model->rotation = rotation;
    model->scale = scale;
    model->render(shader);
}
