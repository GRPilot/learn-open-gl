//
// Created by gollan on 24.03.2021.
//
#include "deps.hpp"
#include "stb_image.h"

#include "texture.hpp"

Texture::Texture(GLenum type, GLenum position)
    : ID(0), TYPE(type), POS(position) {
    glGenTextures(1, &ID);
    bind();
}

Texture::~Texture() {
    if(GL_TRUE == glIsTexture(ID)) {
        glDeleteTextures(1, &ID);
    }
}

void Texture::set(GLenum pname, GLint value) {
    std::cout << "[Info ] [Texture] Set the " << pname << " to " << value << std::endl;
    glTexParameteri(TYPE, pname, value);
}

void Texture::bind() const {
    glActiveTexture(POS);
    glBindTexture(TYPE, ID);
}

void Texture::unbind() const {
    glActiveTexture(0);
    glBindTexture(TYPE, 0);
}

GLuint Texture::id() const {
    return ID;
}

GLenum Texture::type() const {
    return TYPE;
}
