#include "Model.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"

#include "Texture.hpp"

void Model::initModel() {

}

Model::Model(glm::vec3 position, const char* textureDiffusePath, const char* textureSpecularPath, const char* modelPath, const char* modelName) {
    //Init Data
    rotation = glm::vec3(0.f);
    scale = glm::vec3(1.f);
    originPos = glm::vec3(0.f);

    //Set Data
    this->position = position;    
    this->modelName = modelName;

    std::cout << "\n\n" << modelName << "\n";

    textureDiffuse = new Texture(textureDiffusePath, GL_TEXTURE_2D, 0);
    textureSpecular = new Texture(textureSpecularPath, GL_TEXTURE_2D, 1);
    
    try
    {
        ModelLoader loader;
        loader.loadOBJModel(modelPath);
        meshes.push_back(new Mesh(loader.getVertices()));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

Model::~Model() {
    for(auto*& mesh : meshes)
        delete mesh;
    
    delete textureDiffuse;
    delete textureSpecular;
}

void Model::updateUniforms(Shader* shader) {
    ModelMatrix = glm::mat4(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, rotation.x, glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.y, glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, rotation.z, glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::translate(ModelMatrix, originPos);
    ModelMatrix = glm::scale(ModelMatrix, scale);

    shader->setMat4("model", ModelMatrix);
}

void Model::render(Shader* shader, Texture* texture) {
    updateUniforms(shader);


    textureDiffuse->bind();
    textureSpecular->bind();

    shader->setInt("Texture", textureDiffuse->getTexUnit());
    shader->setInt("Texture", textureSpecular->getTexUnit());

    shader->setBool("texEmpty", texture->isEmpty());

    if(!texture->isEmpty()) {
        texture->bind();
        shader->setInt("Texture", texture->getTexUnit());
    }

    for (auto& mesh : meshes) {

        mesh->render();
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}