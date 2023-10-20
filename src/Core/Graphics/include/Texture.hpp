#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include <glad/glad.h>

class Texture {
    GLuint ID;
    int width, height, nrChannels;

public:
    Texture(const char* texturePath, GLenum type);
    ~Texture();

    inline GLuint getTexID() const { return ID; }

    void bind(GLint textureUint, GLenum type);
    void unbind(GLenum type);
};

#endif