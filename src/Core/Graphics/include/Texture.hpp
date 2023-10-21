#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include <glad/glad.h>

class Texture {
    GLuint ID, textureUnit;
    GLenum type;

    int width, height, nrChannels;

public:
    Texture(const char* texturePath, GLenum type, GLuint textureUnit);
    ~Texture();

    inline GLuint getTexID() const { return ID; }

    GLuint getTexUnit() { return textureUnit; }

    void bind();
    void unbind(GLenum type);
};

#endif