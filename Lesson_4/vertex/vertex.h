#ifndef __VERTEX_H__
#define __VERTEX_H__

namespace glm {
    class vec3;
    class vec4;
} // namespace glm

struct Vertex {
    glm::vec3 position{};
    glm::vec4 color{};
};

constexpr GLsizeiptr POSITION_COUNT = decltype(Vertex::position)::length();
constexpr GLsizeiptr POSITION_SIZE = sizeof(decltype(Vertex::position)::value_type) * POSITION_COUNT;
constexpr GLsizeiptr COLOR_COUNT = decltype(Vertex::color)::length();
constexpr GLsizeiptr COLOR_SIZE = sizeof(decltype(Vertex::color)::value_type) * glm::u8vec4::length();

#endif // __VERTEX_H__
