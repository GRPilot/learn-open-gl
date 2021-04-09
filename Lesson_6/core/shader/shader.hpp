//
// Created by gollan on 13.03.2021.
//

#ifndef LESSON_6_TEXTURES_SHADER_HPP
#define LESSON_6_TEXTURES_SHADER_HPP

namespace ShaderTypes{
    const std::string VERTEX_TYPE = "Vertex shader";
    const std::string FRAGMENT_TYPE = "Fragment shader";
    const std::string PROGRAM_TYPE = "Shader program";
}; // namespace ShaderTypes

class Shader {
public:
    explicit Shader(const std::string &vertexFilename, const std::string &fragmentFilename);
    virtual ~Shader();

    void use() const;

    GLint location(const std::string &attribute) const;
    GLint uniformLocation(const std::string &property) const;

    void set(const std::string &property, int value);
    void set(const std::string &property, unsigned value);
    void set(const std::string &property, bool value);
    void set(const std::string &property, float value);
    void set(const std::string &property, glm::vec2 value);
    void set(const std::string &property, glm::vec3 value);
    void set(const std::string &property, glm::vec4 value);
private:
    GLuint program;

    bool check(GLuint target, const std::string &type) const;
    std::string getErrorMessage(GLuint target, const std::string &type) const;
    std::string loadSource(const std::string &filename) const;
    GLuint createShader(GLenum type, const std::string &src) const;
};


#endif //LESSON_6_TEXTURES_SHADER_HPP
