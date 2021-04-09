//
// Created by gollan on 13.03.2021.
//
#include "deps.hpp"

#include "mash.hpp"

#include <utility>
#include "shader.hpp"
#include "vertex.hpp"

Mash::Mash(const Vertices &vertices, std::shared_ptr<Shader> _shader)
    : shader(_shader),
      VAO(create(BufferType::VAO_TYPE)),
      VBO(create(BufferType::VBO_TYPE)),
      EBO(create(BufferType::EBO_TYPE)),
      drawCount(vertices.indices.size()) {
    if(nullptr == shader) {
        std::cerr << "[Error] [Mash] The shader is null" << std::endl;
        return;
    }

    const decltype(vertices.vertices) &verts = vertices.vertices;
    const decltype(vertices.indices) &inds = vertices.indices;
    if(verts.empty() || inds.empty()) {
        std::cerr << "[Warn ] [Mash] The vertices is empty" << std::endl;
        return;
    }

    auto setVertexAttribute = [this](const std::string &attribute, size_t count, size_t offset) {
        GLint id = shader->location(attribute);
        if(id < 0) {
            std::cerr << "[Error] [Mash] Cannot get location of '" << attribute << "': " << id << std::endl;
            return;
        }
        glVertexAttribPointer(id, count, GL_FLOAT, GL_FALSE, Vertex::stride(), (void *)offset);
        glEnableVertexAttribArray(id);
    };

    glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), verts.data(), GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(inds[0]), inds.data(), GL_STATIC_DRAW);

      setVertexAttribute("position", Vertex::positionCount(), Vertex::positionOffset());
      setVertexAttribute("color", Vertex::colorCount(), Vertex::colorOffset());
      setVertexAttribute("texture_position", Vertex::textureCount(), Vertex::textureOffset());

     glBindVertexArray(0);
}

Mash::~Mash() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}


void Mash::draw(GLenum mode) {
    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(mode, drawCount, GL_UNSIGNED_INT, nullptr);
}

GLuint Mash::create(Mash::BufferType type) {
    GLuint newBuffer = 0;
    switch(type) {
        case BufferType::VAO_TYPE:
            glGenVertexArrays(1, &newBuffer);
            break;
        case BufferType::VBO_TYPE:
        case BufferType::EBO_TYPE:
            glGenBuffers(1, &newBuffer);
            break;
    }
    return newBuffer;
}

