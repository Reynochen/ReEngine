#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "GUI.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"

GUI::GUI(Anchor pin, glm::vec4 color, bool Enable, const char* texPath, bool fillX, bool fillY) 
{
        this->Enable = Enable;
        this->scale = 100;
        
        this->color = color;

        this->pin = pin;

        // createCube();
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

    float height = Window::getHeight();
    float width = Window::getWidth();

    shader->use();
    shader->setFloat("time", (float)glfwGetTime());
    shader->setBool("texEmpty", texture->isEmpty());
    
    if(flexible) createFlexibleCube(width, height);
    
    ModelMatrix = glm::mat4(1.f);

    // Anchor
    switch (pin)
    {
    case UP:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,1,0));
        break;
    case DOWN:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,-1,0));
        break;
    case LEFT:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-1,0,0));
        break;
    case RIGHT:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1,0,0));
        break;    
    default:
    case CENTER:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,0,0));
        break;
    }
    
    // ModelMatrix += glm::translate(ModelMatrix, glm::vec3(1/height, 1/height, 0));

    // // Scaling by resize window
    // if(!flexible)
    //     ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f / width*SIZE*2,
    //                                                     1.f / height*SIZE*2,
    //                                                     1.f));

    // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(xPos, yPos, 0));

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

void GUI::createFlexibleCube(float widthWin, float heightWin)
{
    // std::cout <<"Creating cube\n";
    for (auto mesh : meshes) {
        delete mesh;
        meshes.clear();
    }

    //Padding
    float lPadding = xPos + leftPadding;
    float rPadding = -xPos + rightPadding;
    float tPadding = -yPos + topPadding;
    float bPadding = yPos + bottomPadding;
    
    //Static
    float sqAspectRatio = 1280 / 720;
    float aspectRatio = widthWin / heightWin;
    float sqWidth = 1.0f*scale;
    float sqHeight = 0.25f*scale;
    
    sqWidth = sqAspectRatio / aspectRatio;


    glm::vec3 sqVertices[] = {
        /*All Flexible*/
                    //x                                      //y
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,           1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f), //Left bottom
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin, 1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin, 1.0f - 2.0f * tPadding / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,           1.0f - 2.0f * tPadding / heightWin, 0.0f)
        
        /*No Flexible*/
        // glm::vec3(-sqWidth / 2.0f, -sqHeight / 2.0f, 0),
        // glm::vec3(sqWidth / 2.0f, -sqHeight / 2.0f, 0),
        // glm::vec3(sqWidth / 2.0f, sqHeight / 2.0f, 0),
        // glm::vec3(-sqWidth / 2.0f, sqHeight / 2.0f, 0),
        
        /*Flexible X and pin Height*/
        glm::vec3(-1.0f + 2.0f * lPadding / widthWin,               (-sqHeight+yPos) / heightWin    / 2.0f, 0),
        glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,  (-sqHeight+yPos) / heightWin    / 2.0f, 0),
        glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,  sqHeight/scale / 2.0f, 0),
        glm::vec3(-1.0f + 2.0f * lPadding / widthWin,               sqHeight/scale / 2.0f, 0),
    };

    // float sqVertices[] = {
    //     -sqWidth / 2.0f, -sqHeight / 2.0f    // Bottom-left
    //     sqWidth / 2.0f, -sqHeight / 2.0f,    // Bottom-right
    //     sqWidth / 2.0f,  sqHeight / 2.0f,    // Top-right
    //     -sqWidth / 2.0f,  sqHeight / 2.0f,   // Top-left
    // };

    meshes.push_back(new Mesh(new std::vector<Vertex>{
                //Pos               //Color              //TexCoord         //Normal
        Vertex {sqVertices[0],    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {sqVertices[1],    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {sqVertices[2],    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},
        Vertex {sqVertices[3],    glm::vec4(color),    glm::vec2(1.f),    glm::vec3(0.f)},    
    }));

    meshes[0]->mode = GL_TRIANGLE_FAN;  

}