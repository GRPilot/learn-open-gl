//
// Created by gollan on 13.03.2021.
//

#ifndef LESSON_6_TEXTURES_MASH_HPP
#define LESSON_6_TEXTURES_MASH_HPP

class Shader;
class Vertices;

class Mash {
public:
    explicit Mash(const Vertices &vertices, std::shared_ptr<Shader> shader);
    virtual ~Mash();

    void draw(GLenum mode = GL_TRIANGLES);

private:
    std::shared_ptr<Shader> shader;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint drawCount;

    enum class BufferType : uint8_t {
        VAO_TYPE,
        VBO_TYPE,
        EBO_TYPE
    };
    static GLuint create(BufferType type);
};


#endif //LESSON_6_TEXTURES_MASH_HPP
