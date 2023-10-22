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
    this->position = position;
    this->textureDiffuse = textureDiffuse;
    this->textureSpecular = textureSpecular;

    try
    {
        meshes.push_back(new Mesh(loadOBJ(modelPath)));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    // for(auto* mesh : meshes) {
    //     this->meshes.push_back(new Mesh(*mesh));
    // }

}

Model::~Model() {
    for(auto*& mesh : meshes)
        delete mesh;
}

void Model::updateUniforms(Shader* shader) {

}

void Model::render(Shader* shader) {
    updateUniforms(shader);

    shader->use();

    for (auto& mesh : meshes) {
        textureDiffuse->bind();
        textureSpecular->bind();

        mesh->render(shader);
    }
}