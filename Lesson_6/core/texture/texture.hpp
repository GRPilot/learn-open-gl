//
// Created by gollan on 24.03.2021.
//

#ifndef LESSON_6_TEXTURES_TEXTURE_HPP
#define LESSON_6_TEXTURES_TEXTURE_HPP

class Texture {
public:
    explicit Texture(GLenum type, GLenum position);
    virtual ~Texture();

    void set(GLenum pname, GLint value);
    virtual int load(const std::string &texFilename) = 0;
    virtual void bind() const;
    virtual void unbind() const;
    GLuint id() const;
    GLenum type() const;

protected:
    GLuint ID;
    GLenum TYPE;
    GLenum POS;
};

using TexturePtr = std::shared_ptr<Texture>;

#endif //LESSON_6_TEXTURES_TEXTURE_HPP
