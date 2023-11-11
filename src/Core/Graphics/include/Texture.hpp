#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include <glad/glad.h>

class Texture {
    GLuint ID, textureUnit;
    GLenum type;

    int width, height, nrChannels;
    bool empty = true;

public:
    Texture(const char* texturePath, GLenum type, GLuint textureUnit);
    ~Texture();

    GLuint getTexID() const { return ID; }

    GLuint getTexUnit() { return textureUnit; }

    bool isEmpty() { return empty; }

    void bind();
    void unbind(GLenum type);
};

#endif