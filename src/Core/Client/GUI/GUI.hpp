#ifndef ENGINE_GUI
#define ENGINE_GUI

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>

class Mesh;
class Shader;
class Texture;

class GUI {
    std::vector<Mesh*> meshes;
    Texture* texture = nullptr;
    glm::vec4 color;

    glm::mat4 ModelMatrix;
    int SIZE=250;

    bool Enable = true;

public:
    GUI();
    ~GUI();    

    void render(Shader* shader);

};

#endif