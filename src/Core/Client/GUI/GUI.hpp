#ifndef ENGINE_GUI
#define ENGINE_GUI

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include <string>

class Mesh;

class GUI {
    std::vector<Mesh*> meshes;

public:
    GUI();
    ~GUI();    

};

#endif