//
// Created by gollan on 13.03.2021.
//
#include "deps.hpp"

#include "shader.hpp"

namespace std {
    ostream &operator<<(ostream &out, const glm::vec2 &vec) {
        out << "(" << vec[0] << ", " << vec[1] << ")";
        return out;
    }
    ostream &operator<<(ostream &out, const glm::vec3 &vec) {
        out << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
        return out;
    }
    ostream &operator<<(ostream &out, const glm::vec4 &vec) {
        out << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << ")";
        return out;
    }
}

Shader::Shader(const std::string &vertexFilename, const std::string &fragmentFilename)
    : program(glCreateProgram()) {
    GLuint vertex = createShader(GL_VERTEX_SHADER, loadSource(vertexFilename));
    if(!check(vertex, ShaderTypes::VERTEX_TYPE)) {
        std::cerr << "[Error] [Shader] The compilation of " << ShaderTypes::VERTEX_TYPE << " was failed:" << std::endl;
        std::cerr << getErrorMessage(vertex, ShaderTypes::VERTEX_TYPE) << std::endl;
    }
    GLuint fragment = createShader(GL_FRAGMENT_SHADER, loadSource(fragmentFilename));
    if(!check(fragment, ShaderTypes::FRAGMENT_TYPE)) {
        std::cerr << "[Error] [Shader] The compilation of " << ShaderTypes::FRAGMENT_TYPE << " was failed:" << std::endl;
        std::cerr << getErrorMessage(vertex, ShaderTypes::FRAGMENT_TYPE) << std::endl;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    if(!check(program, ShaderTypes::PROGRAM_TYPE)) {
        std::cerr << "[Error] [Shader] The linking of " << ShaderTypes::PROGRAM_TYPE << " was failed:" << std::endl;
        std::cerr << getErrorMessage(program, ShaderTypes::PROGRAM_TYPE) << std::endl;
        return;
    }
    std::cout << "[Info ] [Shader#" << program << "] Shader program was successfully created" << std::endl;
}

Shader::~Shader() {
    if(glIsProgram(program)) {
        glDeleteProgram(program);
    }
}

void Shader::use() const {
    glUseProgram(program);
}

GLint Shader::location(const std::string &attribute) const {
    return glGetAttribLocation(program, attribute.c_str());
}

GLint Shader::uniformLocation(const std::string &property) const {
    return glGetUniformLocation(program, property.c_str());
}

void Shader::set(const std::string &property, int value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform1i(uniformLocation(property), value);
}
void Shader::set(const std::string &property, unsigned int value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform1ui(uniformLocation(property), value);
}
void Shader::set(const std::string &property, bool value) {
    set(property, static_cast<int>(value));
}
void Shader::set(const std::string &property, float value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform1f(uniformLocation(property), value);
}
void Shader::set(const std::string &property, glm::vec2 value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform2f(uniformLocation(property), value[0], value[1]);
}
void Shader::set(const std::string &property, glm::vec3 value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform3f(uniformLocation(property), value[0], value[1], value[2]);
}
void Shader::set(const std::string &property, glm::vec4 value) {
    std::cout << "[Info ] [Shader] Set " << property << " by value " << value << std::endl;
    glUniform4f(uniformLocation(property), value[0], value[1], value[2], value[3]);
}

bool Shader::check(GLuint target, const std::string &type) const {
    bool isShader = type != ShaderTypes::PROGRAM_TYPE;
    int success = GL_FALSE;
    if(isShader) {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
    } else {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
    }
    return GL_TRUE == success;
}

std::string Shader::getErrorMessage(GLuint target, const std::string &type) const {
    bool isShader = type != ShaderTypes::PROGRAM_TYPE;
    GLchar errstr[512]{};
    GLsizei errsize = 0;
    if(isShader) {
        glGetShaderInfoLog(target, sizeof(errstr), &errsize, errstr);
    } else {
        glGetProgramInfoLog(target, sizeof(errstr), &errsize, errstr);
    }
    std::stringstream out;
    const std::string HEADER = "[Error] [Shader] ";
    out << HEADER;
    for(GLsizei i = 0; i < errsize; ++i) {
        if(errstr[i] != '\n') {
            out << errstr[i];
            continue;
        }
        out << std::endl << HEADER;
    }
    return out.str();
}

std::string Shader::loadSource(const std::string &filename) const {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    std::string src;
    try {
        file.open(filename);
        std::stringstream stream;
        stream << file.rdbuf();
        src = stream.str();
    } catch(std::ifstream::failure &e) {
        std::cerr << "[Error] [Shader] Cannot load source from file '" << filename << "'" << std::endl;
        std::cerr << "[Error] [Shader]      " << e.what() << std::endl;
    }
    return src;
}

GLuint Shader::createShader(GLenum type, const std::string &src) const {
    const char *srcstr = src.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &srcstr, nullptr);
    glCompileShader(shader);
    return shader;
}

