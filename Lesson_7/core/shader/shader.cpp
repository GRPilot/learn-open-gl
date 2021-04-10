#include "incs.hpp"
#include "logger.hpp"

#include "shader.hpp"

namespace {
    void printSource(std::string src) {
        if(src.back() == '\n') {
            src.pop_back();
        }

        size_t line = 0;
        std::string strline;
        for(const char c : src) {
            if('\n' == c) {
                LogI("[Shader] %3zd |%s", ++line, strline.c_str());
                strline.clear();
                continue;
            }
            strline += c;
        }
        LogI("[Shader] %3zd |%s", ++line, strline.c_str());
    }
}

Shader::Shader(const std::string &vShader, const std::string &fShader)
    : prog(glCreateProgram()), lastError(nullptr) {
    if(vShader.empty() || fShader.empty()) {
        lastError.reset(new ShaderError{"The pathes to shaders is empty.", -1});
        return;
    }

    GLuint vertex = generateShader(GL_VERTEX_SHADER, vShader);
    if(hasError(vertex, GL_COMPILE_STATUS)) {
        const std::string err = getError(vertex, GL_SHADER);
        LogE("[Shader] %s", err.c_str());
        lastError.reset(new ShaderError{err, -2});
    }
    GLuint fragment = generateShader(GL_FRAGMENT_SHADER, fShader);
    if(hasError(fragment, GL_COMPILE_STATUS)) {
        const std::string err = getError(fragment, GL_SHADER);
        LogE("[Shader] %s", err.c_str());
        lastError.reset(new ShaderError{err, -3});
    }

    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);
    if(hasError(prog, GL_LINK_STATUS)) {
        const std::string err = getError(vertex, GL_SHADER);
        LogE("[Shader] %s", err.c_str());
        lastError.reset(new ShaderError{err, -3});
    }
}

Shader::~Shader() {
    glDeleteProgram(prog);
}

bool Shader::success() const {
    return !static_cast<bool>(lastError);
}

std::shared_ptr<ShaderError> Shader::getLastError() const {
    return lastError;
}

int Shader::location(const std::string &property, PropertyType type) const {
    GLint loc = -1;
    switch(type) {
        case PropertyType::UNIFORM:
            loc = glGetUniformLocation(prog, property.c_str());
            break;
        case PropertyType::ATTRIBUTE:
            loc = glGetAttribLocation(prog, property.c_str());
            break;
    }
    return loc;
}

void Shader::set(const std::string &property, float value) {
    glUniform1f(this->location(property), value);
}

void Shader::set(const std::string &property, int value) {
    glUniform1i(this->location(property), value);
}

void Shader::set(const std::string &property, bool value) {
    glUniform1i(this->location(property), static_cast<int>(value));
}

void Shader::set(const std::string &property, const glm::mat4 &value) {
    glUniformMatrix4fv(this->location(property), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::use() {
    glUseProgram(prog);
}

void Shader::unuse() {
    glUseProgram(0);
}

GLuint Shader::generateShader(GLenum type, const std::string &fpath) const {
    std::string source = loadFormFile(fpath);
    if(source.empty()) {
        return 0;
    }
    LogI("[Shader] Load source from '%s'", fpath.c_str());
    printSource(source);
    GLuint shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    LogI("[Shader] Generated shader: %u", shader);
    return shader;
}

std::string Shader::loadFormFile(const std::string &fname) const try {
    std::ifstream file;
    file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
    file.open(fname);
    std::stringstream strstream;
    strstream << file.rdbuf();
    return strstream.str();
} catch (std::fstream::failure &fail) {
    LogE("[Shader] Cannot load '%s' file: %s", fname.c_str(), fail.what());
    lastError.reset(new ShaderError{fail.what(), fail.code().value()});
    return "";
}

bool Shader::hasError(GLuint target, GLenum what) const {
    if(target == 0) {
        return false;
    }
    int success;
    if(GL_LINK_STATUS == what) {
        glGetProgramiv(target, what, &success);
    } else {
        glGetShaderiv(target, what, &success);
    }
    return GL_TRUE != success;
}

std::string Shader::getError(GLuint target, GLenum type) const {
    if(target == 0) {
        return "Failed while creating";
    }
    char error[2048];
    memset(error, 0, sizeof(error));
    GLsizei errsize;
    if(GL_PROGRAM == type) {
        glGetProgramInfoLog(target, sizeof(error), &errsize, error);
    } else {
        glGetShaderInfoLog(target, sizeof(error), &errsize, error);
    }
    if(nullptr == error || errsize <= 0) {
        return "";
    }

    return std::string(error, errsize);
}
