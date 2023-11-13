#ifndef ENGINE_GUI
#define ENGINE_GUI

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.hpp"

#include "Window.hpp"

enum Anchor {
    UP, DOWN, LEFT, RIGHT, CENTER
};

class Shader;
class Texture;

class GUI {
    std::vector<Mesh*> meshes;
    Texture* texture;
    glm::vec4 color;

    glm::mat4 ModelMatrix;
    float scale;
    Anchor pin;

    float yPos = 0.0, xPos = 0.0;

    void createFlexibleCube(float width, float height);
    
    float rightPadding = 12.0f;
    float leftPadding = 12.0f;
    float topPadding = 450.0f;
    float bottomPadding = 8.0f;

public:
    bool flexible = false;
    bool Enable;

    GUI(Anchor pin = CENTER, glm::vec4 color = glm::vec4(1.f), bool Enable = true, const char* texPath = "", bool fillX = false, bool fillY = false);
    ~GUI();    

    void setX(float x) { xPos += x; }
    void setY(float y) { yPos += y; }
    void setPos(float x, float y);


    void render(Shader* shader);

};

#endif