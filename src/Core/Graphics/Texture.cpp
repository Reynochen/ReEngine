#include "Texture.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include <stb_image.h>

Texture::Texture(const char* texturePath, GLenum type, GLuint textureUnit) : textureUnit(textureUnit), type(type) {
    if(ID) glDeleteTextures(1, &ID);

    this->type = type;
    this->textureUnit = textureUnit;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(texturePath, &width, &height, &nrChannels, 4);

    if(!image) {
        const char* empty = "";
        if(texturePath[0] != empty[0])
            std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED \"" << texturePath << "\"\n";
        
        stbi_image_free(image);
        return;
    }

    createTexture(image);
    stbi_image_free(image);
}

void Texture::createTexture(unsigned char* image) {
    glGenTextures(1, &ID);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapParam);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(type);

    glActiveTexture(0);
    glBindTexture(type, 0);

    this->empty = false;
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(type, ID);
}

void Texture::unbind(GLenum type) {
    glActiveTexture(0);
    glBindTexture(type, 0);
}