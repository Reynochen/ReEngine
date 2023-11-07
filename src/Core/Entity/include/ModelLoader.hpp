#ifndef MODEL_LOADER
#define MODEL_LOADER

#include <vector>
class Vertex;

class ModelLoader {
    std::vector<Vertex>* vertices = nullptr;

public:
    ModelLoader();

    void loadOBJModel(const char* filePath);
    std::vector<Vertex>* getVertices() { return vertices; }

};

#endif