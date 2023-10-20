#include "Texture.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include <stb_image.h>

Texture::Texture(const char* texturePath, GLenum type) {
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(texturePath, &width, &height, &nrChannels, 4);

    if(!image) {
        std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED \"" << texturePath << "\"\n";
        return;
    }

    glGenTextures(1, &ID);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(type, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(type);

    glActiveTexture(0);
    glBindTexture(type, 0);
    stbi_image_free(image);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind(GLint textureUint, GLenum type) {
    glActiveTexture(GL_TEXTURE0 + textureUint);
    glBindTexture(type, ID);
}

void Texture::unbind(GLenum type) {
    glActiveTexture(0);
    glBindTexture(type, 0);
}