#ifndef ENGINE_GUI
#define ENGINE_GUI

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.hpp"

class Shader;
class Texture;

class GUI {
    std::vector<Mesh*> meshes;
    Texture* texture = nullptr;
    glm::vec4 color;

    glm::mat4 ModelMatrix;
    float SIZE;

    bool fillX, fillY;

    float yPos = 0.0, xPos = 0.0;

public:
    float width = 0, height = 0;
    bool flexible = true;
    bool Enable;

    GUI(float size = 1, bool Enable = true, bool fillX = false, bool fillY = false, glm::vec4 color = glm::vec4(1.f)) 
    {
        this->Enable = Enable;
        this->SIZE = size * 0.01;
        this->fillX = fillX;
        this->fillY = fillY;

        std::vector<Vertex>* cubeVert = new std::vector<Vertex>{
                    //Pos                             //Color              //TexCoord          //Normal
            Vertex {glm::vec3(-1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},
            Vertex {glm::vec3( 1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},
            Vertex {glm::vec3(-1.0f,  1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},

            Vertex {glm::vec3( 1.0f, -1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},
            Vertex {glm::vec3( 1.0f, 1.0f, 0.0f),     glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},
            Vertex {glm::vec3( -1.0f, 1.0f, 0.0f),    glm::vec4(color),    glm::vec2(1.0f),    glm::vec3(0.0f)},      
        };
        meshes.push_back(new Mesh(cubeVert));
    }
    ~GUI();    

    void setX(float x) { xPos = x; }
    void setY(float y) { yPos = y; }
    void setPos(float x, float y);

    void render(Shader* shader);

};

#endif