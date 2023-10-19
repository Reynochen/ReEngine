#ifndef ENGINE_MESH
#define ENGINE_MESH

#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint VAO, VBO, EBO;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 ModelMatrix;

    void initVertexData(Vertex* vertexArray, const unsigned& verticiesCount, GLuint* indexArray, const unsigned& indicesCount);
    void initVAO();
    void initModelMatrix();
    void updateUniforms(Shader* shader);

public:
    Mesh(Vertex* vertexArray, const unsigned& verticiesCount, GLuint* indexArray, const unsigned& indicesCount);
    ~Mesh();

    void update();
    void render(Shader* shader);
};

#endif