#include "Mesh.hpp"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"


Mesh::Mesh(Vertex* vertexArray, const unsigned& verticesCount, GLuint* indexArray, const unsigned& indicesCount) 
{
    initVertexData(vertexArray, verticesCount, indexArray, indicesCount);
    initVAO();
    initModelMatrix();
}
Mesh::Mesh(std::vector<Vertex> vertices) 
{
    this->vertices = vertices;

    initVAO();
    initModelMatrix();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::initVertexData(Vertex* vertexArray, const unsigned& verticesCount, GLuint* indexArray, const unsigned& indicesCount) 
{
    for(size_t i = 0; i < verticesCount; i++) {
        this->vertices.push_back(vertexArray[i]);     
    }    

    for(size_t i = 0; i < indicesCount; i++) {
        this->indices.push_back(indexArray[i]);     
    }

}

void Mesh::initVAO() 
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &this->EBO);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Mesh::initModelMatrix() 
{
    position = glm::vec3(0.f);
    rotation = glm::vec3(0.f);
    scale = glm::vec3(1.f);

    ModelMatrix = glm::mat4(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);
}

void Mesh::updateUniforms(Shader* shader) 
{
    ModelMatrix = glm::scale(ModelMatrix, scale);

    shader->setMat4("model", ModelMatrix);
    ModelMatrix = glm::mat4(1.f);
}

//Probably i should make this a little better
void Mesh::setPosition(glm::vec3 pos) 
{
    position = pos;
    ModelMatrix = glm::translate(ModelMatrix, position);
}
void Mesh::rotate(glm::vec3 rotate) 
{
    rotation = rotate;
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
}

void Mesh::render(Shader* shader) 
{
    //Update uniforms in shader
    updateUniforms(shader);

    //Render
    glBindVertexArray(VAO);

    if(indices.empty())
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    else
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}