#include <vector>
#include <glm/glm.hpp>

#include "GUI.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

#include "Window.hpp"

GUI::GUI() 
{
    std::vector<Vertex>* cubeVert = new std::vector<Vertex>{
                //Pos                            //Color             //TexCoord          //Normal
        Vertex {glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
        Vertex {glm::vec3( 0.5f, -0.5f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
        Vertex {glm::vec3( 0.0f,  0.5f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
    };

    meshes.push_back(new Mesh(cubeVert));
}

GUI::~GUI() 
{
    for(auto*& mesh : meshes)
        delete mesh;

    delete texture;
}

void GUI::render(Shader* shader)
{
    glDisable(GL_DEPTH_TEST);
    shader->use();
    ModelMatrix = glm::mat4(1.f);

    float width = Window::getWidth()/100 * 20;
    float height = Window::getHeight()/100 * 20;

    if(width > 100) {
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f / (width/100), 1, 1));
    }
    if(height > 100) {
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 1.f / (height/100), 1));
    }

    shader->setMat4("model", ModelMatrix);

    for (auto& mesh : meshes) {
        if(texture != nullptr) {
            texture->bind();
            shader->setInt("Texture", texture->getTexUnit());
        }

        mesh->render();
    }
    glEnable(GL_DEPTH_TEST);
}