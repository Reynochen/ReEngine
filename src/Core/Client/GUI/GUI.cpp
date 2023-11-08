#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "GUI.hpp"
#include "Graphics.hpp"

void GUI::setPos(float x, float y) {
    xPos = x;
    yPos = y;
}

GUI::~GUI() 
{
    for(auto*& mesh : meshes)
        delete mesh;

    delete texture;
}

void GUI::render(Shader* shader)
{
    if(!Enable) return;
    glDisable(GL_DEPTH_TEST);

    float widthWin = Window::getWidth();
    float heightWin = Window::getHeight(); 

    shader->use();
    shader->setFloat("time", (float)glfwGetTime());
    ModelMatrix = glm::mat4(1.f);
    // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, -1, 0));
    
    //Scaling widget in Y axis
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(heightWin * SIZE));
    //Pin widget
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(xPos/SIZE/heightWin, yPos/SIZE/heightWin, 0));
    //Scaling by resize window
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3((fillX) ? widthWin : (flexibility) ? 1.f / widthWin + width/(widthWin+heightWin) : 1.f / widthWin,
                                                    (fillY) ? heightWin : (flexibility) ? 1.f / heightWin + height/(widthWin+heightWin) : 1.f / heightWin, 
                                                    1.f));
    
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