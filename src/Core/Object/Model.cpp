#include "Model.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"

#include "Texture.hpp"

void Model::initModel() {

}

Model::Model(glm::vec3 position, Texture* textureDiffuse, Texture* textureSpecular, std::vector<Mesh*> meshes) {
    this->position = position;
    this->textureDiffuse = textureDiffuse;
    this->textureSpecular = textureSpecular;

    for(auto* mesh : meshes) {
        this->meshes.push_back(new Mesh(*mesh));
    }

}

Model::~Model() {
    for(auto*& mesh : meshes)
        delete mesh;
}

void Model::render(Shader* shader) {
    updateUniforms(shader);

    shader->use();

    textureDiffuse->bind();
    textureSpecular->bind();

    for (auto& mesh : meshes)
        mesh->render(shader);
}