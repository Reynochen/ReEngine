#ifndef MODEL_LOADER
#define MODEL_LOADER

#include <glm/glm.hpp>
#include <string>
#include <vector>
class Vertex;

class ModelLoader {
    std::vector<Vertex>* vertices = nullptr;

    void readFace(std::vector<std::string>& words, std::vector<glm::vec3>&v, std::vector<glm::vec2>&vt, std::vector<glm::vec3>&vn, std::vector<Vertex>& vert);
    void readCorner(std::string& word, std::vector<glm::vec3>&v, std::vector<glm::vec2>&vt, std::vector<glm::vec3>&vn, std::vector<Vertex>& vert);

public:
    ModelLoader();

    void loadOBJModel(const char* filePath);
    std::vector<Vertex>* getVertices() { return vertices; }

};

#endif