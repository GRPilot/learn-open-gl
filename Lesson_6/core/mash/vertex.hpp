//
// Created by gollan on 13.03.2021.
//

#ifndef LESSON_6_TEXTURES_VERTEX_HPP
#define LESSON_6_TEXTURES_VERTEX_HPP


#pragma pack(push, 1)
struct Vertex {
    Vertex(const glm::vec3 &position,
           const glm::vec4 &color,
           const glm::vec2 &texturePosition);

    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_position;

    static GLsizei positionCount();
    static GLsizei colorCount();
    static GLsizei textureCount();

    static size_t positionOffset();
    static size_t colorOffset();
    static size_t textureOffset();

    static GLsizei stride();
};
#pragma pack(pop)

struct Vertices {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

#endif //LESSON_6_TEXTURES_VERTEX_HPP
