#ifndef ENGINE_MESH
#define ENGINE_MESH

#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
    glm::vec4 color;
};


class Mesh {
    std::vector<Vertex>* vertices;
    std::vector<GLuint> indices;

    GLuint VAO, VBO, EBO;

    void initVertexData(Vertex* vertexArray, const unsigned& verticesCount, GLuint* indexArray, const unsigned& indicesCount);
    void initVAO();

public:
    GLenum mode = GL_TRIANGLES;
    
    Mesh(Vertex* vertexArray, const unsigned& verticesCount, GLuint* indexArray, const unsigned& indicesCount);
    Mesh(std::vector<Vertex>* vertices);

    ~Mesh();

    void render();
};

#endif