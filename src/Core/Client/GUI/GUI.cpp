#include <vector>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "GUI.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"

GUI::GUI(Anchor pin, glm::vec4 color, bool Enable, float sqWidth, float sqHeight, const char* texPath, bool fillX, bool fillY) 
{
        this->Enable = Enable;
        this->scale = 1;
        
        this->color = color;

        this->pin = pin;

        this->sqOriginWidth = sqWidth;
        this->sqOriginHeight = sqHeight;

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

    float widthWin = Window::getWidth();
    float heightWin = Window::getHeight();

    shader->use();
    shader->setFloat("time", (float)glfwGetTime());
    
    if(flexible) createFlexibleCube(widthWin, heightWin);
    else createStaticCube(widthWin, heightWin);
    
    ModelMatrix = glm::mat4(1.f);


    // Anchor
    // Anchor localPin = pin;
    // if(flexible && scalableY && scalableX) localPin = CENTER;
    switch (pin)
    {
    case TOP:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,1,0));
        break;
    case BOTTOM:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,-1,0));
        break;
    case LEFT:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-1,0,0));
        break;
    case RIGHT:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1,0,0));
        break;  

    case LEFTBOT:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-1,-1,0));
        break;
    default:
    case CENTER:
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,0,0));
        break;
    }
    
    shader->setMat4("model", ModelMatrix);
    shader->setBool("texEmpty", texture->isEmpty());
    if(!texture->isEmpty()) {
        texture->bind();
        shader->setInt("Texture", texture->getTexUnit());
    }

    updateMesh();
    for (auto& mesh : meshes) {        
        mesh->render();
    }
    glEnable(GL_DEPTH_TEST);
}

void GUI::createStaticCube(float widthWin, float heightWin)
{    
    //Static
    float sqWidth = sqOriginWidth*scale;
    float sqHeight = sqOriginHeight*scale;

    if(scalableY) {
        sqWidth *= heightWin/1000;
        sqHeight *= heightWin/1000;
    }

    sqVertices = new glm::vec3[] {
        /*All Flexible*/
                     //x                                                 //y
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,                1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f), //Left bottom
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,   1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,   1.0f - 2.0f * tPadding / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,                1.0f - 2.0f * tPadding / heightWin, 0.0f),

        /*scalableY static*/
        glm::vec3((-sqWidth + xPos/480)*200/ widthWin,  (-sqHeight+yPos/480)*200/ heightWin, 0),
        glm::vec3((sqWidth + xPos/480)*200/ widthWin,   (-sqHeight+yPos/480)*200/ heightWin, 0),
        glm::vec3((sqWidth + xPos/480)*200/ widthWin,    (sqHeight+yPos/480)*200/ heightWin, 0),
        glm::vec3((-sqWidth + xPos/480)*200/ widthWin,  (sqHeight+yPos/480)*200/ heightWin, 0),

        /*No Flexible*/
        // glm::vec3((-sqWidth+xPos*10/widthWin), (-sqHeight+yPos*50), 0),
        // glm::vec3((sqWidth+xPos*10/widthWin),  (-sqHeight+yPos*50), 0),
        // glm::vec3((sqWidth+xPos*10/widthWin),  (sqHeight+yPos*50), 0),
        // glm::vec3((-sqWidth+xPos*10/widthWin), (sqHeight+yPos*50), 0)

        
        /*Flexible X and pin Height*/
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,               (-sqHeight+yPos) / heightWin   , 0),
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,  (-sqHeight+yPos) / heightWin   , 0),
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,  sqHeight/scale, 0),
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,               sqHeight/scale, 0),
    };

    // float sqVertices[] = {
    //     -sqWidth, -sqHeight    // Bottom-left
    //     sqWidth, -sqHeight,    // Bottom-right
    //     sqWidth,  sqHeight,    // Top-right
    //     -sqWidth,  sqHeight,   // Top-left
    // };

}

void GUI::createFlexibleCube(float widthWin, float heightWin) 
{
    //Padding
    float lPadding = xPos + leftPadding;
    float rPadding = -xPos + rightPadding;
    float tPadding = -yPos + topPadding;
    float bPadding = yPos + bottomPadding;
    
    //Static
    float sqWidth = sqOriginWidth*scale;
    float sqHeight = sqOriginHeight*scale;
    
    // sqWidth /= aspectRatio;

    // sqHeight = sqHeight*200 / heightWin;

    sqVertices = new glm::vec3[] {
        /*All Flexible*/
                     //x                                                 //y
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,                1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f), //Left bottom
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,   1.0f - 2.0f * (heightWin - bPadding) / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * (widthWin - rPadding) / widthWin,   1.0f - 2.0f * tPadding / heightWin, 0.0f),
        // glm::vec3(-1.0f + 2.0f * lPadding / widthWin,                1.0f - 2.0f * tPadding / heightWin, 0.0f),

        
        /*No Flexible*/
        // glm::vec3(-sqWidth, (-sqHeight+yPos)/heightWin, 0),
        // glm::vec3(sqWidth,  (-sqHeight+yPos)/heightWin, 0),
        // glm::vec3(sqWidth,  (sqHeight+yPos)/heightWin+1, 0),
        // glm::vec3(-sqWidth, (sqHeight+yPos)/heightWin+1, 0),

        /*No Flexible*/
        // glm::vec3((-sqWidth+xPos*10/widthWin), (-sqHeight+yPos/50), 0),
        // glm::vec3((sqWidth+xPos*10/widthWin),  (-sqHeight+yPos/50), 0),
        // glm::vec3((sqWidth+xPos*10/widthWin),  (sqHeight+yPos/50), 0),
        // glm::vec3((-sqWidth+xPos*10/widthWin), (sqHeight+yPos/50), 0)

        /*Flexible X and pin Height*/
        glm::vec3((scalableX) ? -1.0f + 2.0f * lPadding / widthWin : (-sqWidth + xPos/480)*200/ widthWin,               
                  (scalableY) ? 1.0f - 2.0f * (heightWin - bPadding) / heightWin : (-sqHeight+yPos/480)*200/ heightWin, 0),

        glm::vec3((scalableX) ? -1.0f + 2.0f * (widthWin - rPadding) / widthWin : (sqWidth + xPos/480)*200/ widthWin,  
                  (scalableY) ? 1.0f - 2.0f * (heightWin - bPadding) / heightWin : (-sqHeight+yPos/480)*200/ heightWin, 0),

        glm::vec3((scalableX) ? -1.0f + 2.0f * (widthWin - rPadding) / widthWin : (sqWidth + xPos/480)*200/ widthWin,  
                  (scalableY) ? 1.0f - 2.0f * tPadding / heightWin : (sqHeight+yPos/480)*200/ heightWin, 0),

        glm::vec3((scalableX) ? -1.0f + 2.0f * lPadding / widthWin : (-sqWidth + xPos/480)*200/ widthWin,               
                  (scalableY) ? 1.0f - 2.0f * tPadding / heightWin : (sqHeight+yPos/480)*200/ heightWin, 0),
    };
}

void GUI::updateMesh()
{
    if(sqVertices == nullptr) return;

    for (auto mesh : meshes) {
        delete mesh;
        meshes.clear();
    }
    meshes.push_back(new Mesh(new std::vector<Vertex>{
                //Pos               //Color              //TexCoord         //Normal
        Vertex {sqVertices[0],    glm::vec4(color),    glm::vec2(0.f, 0.f),    glm::vec3(0.f)},
        Vertex {sqVertices[1],    glm::vec4(color),    glm::vec2(1.f, 0.f),    glm::vec3(0.f)},
        Vertex {sqVertices[2],    glm::vec4(color),    glm::vec2(1.f, 1.f),    glm::vec3(0.f)},
        Vertex {sqVertices[3],    glm::vec4(color),    glm::vec2(0.f, 1.f),    glm::vec3(0.f)},  
    }));
    meshes[0]->mode = GL_TRIANGLE_FAN;
    delete sqVertices;
}