#ifndef __SHADER_H__
#define __SHADER_H__

class Shader {
public:
    Shader();
    ~Shader();
    bool addShader(const std::string &fname);
    bool addShader(const std::string &source, GLenum type);
    bool linkShaderProgram();
    GLint getAttributeLocation(const std::string &name);
    void use();

private:
    GLuint shaderprog;

    std::string read_file(const std::string &fname);

    bool checkShaderError(GLuint shader, GLenum stat) const;
    bool checkProgramError(GLenum stat) const;
};

#endif // __SHADER_H__
