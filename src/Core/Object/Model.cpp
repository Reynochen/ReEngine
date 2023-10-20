#include "Model.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"

void Model::initModel() {

}

Model::Model(glm::vec3 position, Texture* texDif, Texture* texSpec, std::vector<Mesh*> meshes) {
    this->position = position;

}

Model::~Model() {

}

void Model::render(Shader* shader) {

}