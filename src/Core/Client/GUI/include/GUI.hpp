#ifndef ENGINE_GUI
#define ENGINE_GUI

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.hpp"

#include "Window.hpp"

enum Anchor {
    TOP, BOTTOM, LEFT, RIGHT, LEFTBOT, CENTER
};

class Shader;
class Texture;

class GUI {
    std::vector<Mesh*> meshes;
    glm::vec3* sqVertices = nullptr;
    Texture* texture;
    glm::vec4 color;

    glm::mat4 ModelMatrix;
    float scale;
    Anchor pin;

    float yPos = 0.0, xPos = 0.0;

    void createStaticCube(float widthWin, float heightWin);
    void createFlexibleCube(float widthWin, float heightWin);
    void updateMesh();
    
    float rightPadding = 12.0f;
    float leftPadding = 12.0f;
    float topPadding = 20.0f;
    float bottomPadding = 12.0f;

public:
    float sqOriginWidth = 1.f, sqOriginHeight = 1.f;

    bool scalableX = true;
    bool scalableY = false;
    bool flexible = false;
    bool Enable;

    GUI(Anchor pin = CENTER, glm::vec4 color = glm::vec4(1.f), bool Enable = true, float sqWidth = 1.f, float sqHeight = 1.f, const char* texPath = "", bool fillX = false, bool fillY = false);
    ~GUI();    

    void setX(float x) { xPos += x; }
    void setY(float y) { yPos += y; }
    void setPos(float x, float y);


    void render(Shader* shader);

};

#endif