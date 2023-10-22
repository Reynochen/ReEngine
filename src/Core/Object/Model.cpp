#include "Model.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "OBJLoader.hpp"

#include "Texture.hpp"

void Model::initModel() {

}

Model::Model(glm::vec3 position, Texture* textureDiffuse, Texture* textureSpecular, const char* modelPath) {
    //Init Data
    this->position = glm::vec3(0.f);
    this->rotation = glm::vec3(0.f);
    this->scale = glm::vec3(1.f);

    //Set Data
    this->position = position;
    this->textureDiffuse = textureDiffuse;
    this->textureSpecular = textureSpecular;

    try
    {
        std::vector<Vertex> modelVertices = loadOBJ(modelPath);
        meshes.push_back(new Mesh(modelVertices));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

Model::~Model() {
    for(auto*& mesh : meshes)
        delete mesh;
}

void Model::updateUniforms(Shader* shader) {
    ModelMatrix = glm::mat4(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, rotation.x, glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.y, glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.z, glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    shader->setMat4("model", ModelMatrix);
}

void Model::render(Shader* shader) {
    updateUniforms(shader);

    shader->use();

    for (auto& mesh : meshes) {
        textureDiffuse->bind();
        textureSpecular->bind();

        shader->setInt("Texture", textureDiffuse->getTexUnit());
        shader->setInt("Texture", textureSpecular->getTexUnit());

        mesh->render();
    }
}