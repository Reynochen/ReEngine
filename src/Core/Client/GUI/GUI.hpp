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
    Texture* texture;
    glm::vec4 color;

    glm::mat4 ModelMatrix;
    float SIZE;

    bool fillX, fillY;

    float yPos = 0.0, xPos = 0.0;

    void createCube();

public:
    float width = 1, height = 1;
    bool flexible = true;
    bool Enable;

    GUI(float size, glm::vec4 color = glm::vec4(1.f), bool Enable = true, const char* texPath = "", bool fillX = false, bool fillY = false);
    ~GUI();    

    void setX(float x) { xPos = x; }
    void setY(float y) { yPos = y; }
    void setPos(float x, float y);


    void render(Shader* shader);

};

#endif