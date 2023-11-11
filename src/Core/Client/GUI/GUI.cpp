#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "GUI.hpp"
#include "Graphics.hpp"

GUI::GUI(float size, glm::vec4 color, bool Enable, const char* texPath, bool fillX, bool fillY) 
{
        this->Enable = Enable;
        this->SIZE = size;
        this->fillX = fillX;
        this->fillY = fillY;
        
        this->color = color;
        createCube();

        texture = new Texture(texPath, GL_TEXTURE_2D, 0);
}

GUI::~GUI() 
{
    for(auto*& mesh : meshes)
        delete mesh;

    delete texture;
}

void GUI::setPos(float x, float y) {
    xPos = x;
    yPos = y;
}


void GUI::render(Shader* shader)
{
    if(!Enable) return;
    glDisable(GL_DEPTH_TEST);

    float widthWin = Window::getWidth();
    float heightWin = Window::getHeight(); 

    shader->use();
    shader->setFloat("time", (float)glfwGetTime());
    shader->setBool("texEmpty", texture->isEmpty());
    ModelMatrix = glm::mat4(1.f);
    // Anchor
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-1.0,0,0)); /* <--- IMPORTANT LINE */

    // // Scaling widget
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(heightWin, heightWin, 1.f));
    // ModelMatrix = glm::scale(ModelMatrix, glm::vec3(width, height, 1));

    // Scaling by resize window
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3((fillX) ? widthWin : 1.f / widthWin*SIZE,
                                                    (fillY) ? heightWin : 1.f / heightWin*SIZE,
                                                    1.f));

    // if(flexible) ModelMatrix = glm::scale(ModelMatrix, glm::vec3(widthWin*0.01,1,1));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(xPos, yPos, 0));

    shader->setMat4("model", ModelMatrix);
    
    for (auto& mesh : meshes) {
        if(!texture->isEmpty()) {
            texture->bind();
            shader->setInt("Texture", texture->getTexUnit());
        }
        
        mesh->render();
    }
    glEnable(GL_DEPTH_TEST);
}

void GUI::createCube()
{
    // std::cout <<"Creating cube\n";
    for (auto mesh : meshes)
        delete mesh;

    meshes.push_back(new Mesh(new std::vector<Vertex>{
                //Pos                             //Color              //TexCoord          //Normal
        Vertex {glm::vec3(-1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {glm::vec3( 1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {glm::vec3(-1.0f,  1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},

        Vertex {glm::vec3( 1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {glm::vec3( 1.0f,  1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {glm::vec3( -1.0f, 1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},      
    }));
}