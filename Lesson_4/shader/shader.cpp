#include "platform.h"
#include "shader.h"

Shader::Shader()
    : shaderprog(glCreateProgram()) {
}
Shader::~Shader() {
    glDeleteProgram(shaderprog);
}

bool Shader::addShader(const std::string &fname) {
    GLenum shader_type;
    const size_t first = fname.find('.') + 1;
    const size_t last = fname.find_last_of('.');
    const std::string file_extend = fname.substr(first, last - first);
    if("vs" == file_extend) {
        shader_type = GL_VERTEX_SHADER;
    } else if("fs" == file_extend) {
        shader_type = GL_FRAGMENT_SHADER;
    } else {
        std::cerr << "[Error] [Shader] File extention is not valid: " << fname << std::endl;
        return false;
    }
    std::cout << "[Info ] [Shader] Add shader: '" << fname << "'" << std::endl;
    return addShader(read_file(fname), shader_type);
}

bool Shader::addShader(const std::string &source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &(source.begin().base()), NULL);
    glCompileShader(shader);
    if(!checkShaderError(shader, GL_COMPILE_STATUS)) {
        std::cerr << "[ERROR] [Shader] Compilation failed." << std::endl;
        return false;
    }

    glAttachShader(shaderprog, shader);
    return true;
}

bool Shader::linkShaderProgram() {
    glLinkProgram(shaderprog);
    return checkProgramError(GL_LINK_STATUS);
}

GLint Shader::getAttributeLocation(const std::string &name) {
    return glGetAttribLocation(shaderprog, static_cast<const GLchar *>(name.data()));
}

void Shader::use() {
    glUseProgram(shaderprog);
}

std::string Shader::read_file(const std::string &fname) {
    std::ifstream file(fname);
    if(!file.is_open()) {
        return "";
    }

    int cline = 0;
    std::cout.setf(std::ios_base::right);

    std::stringstream source;
    std::string line;
    std::cout << "[Info ] [Shader] Loading shader file:" << std::endl;
    std::cout << "    +---- " << fname << " -----------------------------------------" << std::endl;
    while(std::getline(file, line, '\n')) {
        std::cout.width(3);
        std::cout << cline++ << " | " << line << std::endl;
        source << line << "\n";
    }
    std::cout.setf(std::ios_base::left);
    std::cout << "    +---- " << fname << " -----------------------------------------" << std::endl;
    std::cout << "[Info ] [Shader] File done" << std::endl;

    return source.str();
}

bool Shader::checkShaderError(GLuint shader, GLenum stat) const {
    int status = 0;
    glGetShaderiv(shader, stat, &status);
    if(status != GL_TRUE) {
        char errmsg[512]{};
        glGetShaderInfoLog(shader, sizeof(errmsg), NULL, errmsg);
        std::cerr << "[ERROR] [Shader] Shader error:" << std::endl;
        std::cerr << errmsg << std::endl;
    }
    return status == GL_TRUE;
}

bool Shader::checkProgramError(GLenum stat) const {
    int status = 0;
    glGetProgramiv(shaderprog, stat, &status);
    if(status != GL_TRUE) {
        char errmsg[512]{};
        glGetProgramInfoLog(shaderprog, sizeof(errmsg), NULL, errmsg);
        std::cerr << "[ERROR] [Shader] Program error:" << std::endl;
        std::cerr << errmsg << std::endl;
    }
    return status == GL_TRUE;
}
