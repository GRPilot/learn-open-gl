#ifndef __TEXTUREGEN_H__
#define __TEXTUREGEN_H__

class Texture;

class TextureGenerator {
public:
    using ParamType = std::map<GLenum, GLint>;
    static std::shared_ptr<Texture> generate(GLenum type, const std::string &imgpath, const ParamType &params);
};

#endif // __TEXTUREGEN_H__
