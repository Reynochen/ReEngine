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
        Vertex {glm::vec3(-1.0f, -1.0f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
        Vertex {glm::vec3( 1.0f, -1.0f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
        Vertex {glm::vec3( 0.0f,  1.0f, 0.0f),    glm::vec4(1.0f),    glm::vec2(1.0f),    glm::vec3(0.0f)},
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
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, -0.5, 0));
    
    float width = Window::getWidth();
    float height = Window::getHeight();

    // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1, -75.5/(height*0.1), 0));

    if(width > SIZE) {
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f / (width/SIZE), 1, 1));
    }
    if(height > SIZE) {
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 1.f / (height/SIZE), 1));
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