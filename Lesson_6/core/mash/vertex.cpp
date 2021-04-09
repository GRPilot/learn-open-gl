//
// Created by gollan on 13.03.2021.
//
#include "deps.hpp"

#include "vertex.hpp"

Vertex::Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texturePosition)
    : position(position), color(color), texture_position(texturePosition) {}

GLsizei Vertex::positionCount() {
    return decltype(position)::length();
}

GLsizei Vertex::colorCount() {
    return decltype(color)::length();
}

GLsizei Vertex::textureCount() {
    return decltype(texture_position)::length();
}

size_t Vertex::positionOffset() {
    return 0;
}

size_t Vertex::colorOffset() {
    const size_t offset = positionCount() * sizeof(decltype(position)::value_type);
    return offset;
}

size_t Vertex::textureOffset() {
    const size_t offset = colorOffset() + colorCount() * sizeof(decltype(color)::value_type);
    return offset;
}

GLsizei Vertex::stride() {
    return (
        positionCount() * sizeof(decltype(position)::value_type) +
        colorCount() * sizeof(decltype(color)::value_type) +
        textureCount() * sizeof(decltype(texture_position)::value_type)
    );
}
