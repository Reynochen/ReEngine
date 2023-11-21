#ifndef ENGINE_TEXTURE
#define ENGINE_TEXTURE

#include <glad/glad.h>

class Texture {
    GLuint ID, textureUnit;
    GLenum type;
    GLenum format = GL_RGBA;
    GLint wrapParam = GL_REPEAT;

    int width, height, nrChannels;
    bool empty = true;

    void createTexture(unsigned char* image);

public:
    Texture() {};
    Texture(const char* texturePath, GLenum type, GLuint textureUnit);
    Texture(unsigned char* image, GLenum type, GLuint textureUnit, int width, int height, GLenum format = GL_RGBA, GLint wrapParam = GL_REPEAT) : wrapParam(wrapParam), format(format), textureUnit(textureUnit), type(type), width(width), height(height) { createTexture(image); }
    ~Texture();

    GLuint getTexID() const { return ID; }

    GLuint getTexUnit() { return textureUnit; }

    bool isEmpty() { return empty; }

    void bind();
    void unbind(GLenum type);
};

#endif