#include "deps.hpp"
#include "stb_image.h"

#include "texturegen.hpp"
#include "texture.hpp"

namespace {
    struct Img {
        GLubyte *source;
        int width{-1};
        int height{-1};
        int nrChannels{-1};
        explicit Img(const std::string &path) {
            stbi_set_flip_vertically_on_load(true);
            source = ::stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
            if(!valid()) {
                std::cout << "[Info ] [Texture] Cannot load '" << path << "' image" << std::endl;
                return;
            }
            std::cout << "[Info ] [Texture] The '" << path << "' was successfully loaded:" << std::endl;
            std::cout << "[Info ] [Texture] Texture width: " << width << std::endl;
            std::cout << "[Info ] [Texture] Texture height: " << height << std::endl;
            std::cout << "[Info ] [Texture] Texture channels: " << nrChannels << std::endl;
        }
        ~Img() {
            if(nullptr != source) {
                ::stbi_image_free(source);
                source = nullptr;
            }
        }
        bool valid() const {
            return nullptr != source;
        }
        GLenum getChannels() const {
            switch(nrChannels) {
                case 3: return GL_RGB;
                case 4: return GL_RGBA;
                default: return GL_FALSE;
            }
        }
    };
}

class Texture1D : public Texture {
public:
    explicit Texture1D(GLenum type, GLenum pos) : Texture(type, pos) {}
    int load(const std::string &texFilename) override {
        if(GL_FALSE == glIsTexture(ID)) {
            std::cerr << "[Error] [Texture] Cannot load texture source. Texture ID is invalid" << std::endl;
            return -1;
        }
        Img image(texFilename);
        if(!image.valid()) {
            return -2;
        }
        glTexImage1D(TYPE, image.getChannels(), 0, image.width, 0,
                     image.getChannels(), GL_UNSIGNED_BYTE, image.source);
        glGenerateMipmap(TYPE);
        return 0;
    }
};

class Texture2D : public Texture {
public:
    explicit Texture2D(GLenum type, GLenum pos) : Texture(type, pos) {}
    int load(const std::string &texFilename) override {
        if(GL_FALSE == glIsTexture(ID)) {
            std::cerr << "[Error] [Texture] Cannot load texture source. Texture ID is invalid" << std::endl;
            return -1;
        }
        Img image(texFilename);
        if(!image.valid()) {
            return -2;
        }
        glTexImage2D(TYPE, 0, image.getChannels(), image.width, image.height,
                     0, image.getChannels(), GL_UNSIGNED_BYTE, image.source);
        glGenerateMipmap(TYPE);
        return 0;
    }
};

class Texture3D : public Texture {
public:
    explicit Texture3D(GLenum type, GLenum pos) : Texture(type, pos) {}
    int load(const std::string &texFilename) override {
        if(GL_FALSE == glIsTexture(ID)) {
            std::cerr << "[Error] [Texture] Cannot load texture source. Texture ID is invalid" << std::endl;
            return -1;
        }
        Img image(texFilename);
        if(!image.valid()) {
            return -2;
        }
        const int deep = 0; // WTF and HOW???
        glTexImage3D(TYPE, 0, image.getChannels(), image.width, image.height, deep,
                     0, image.getChannels(), GL_UNSIGNED_BYTE, image.source);
        glGenerateMipmap(TYPE);
        return 0;
    }
};

TexturePtr TextureGenerator::generate(GLenum type, const std::string &imgpath, const ParamType &params) {
    static GLenum position = GL_TEXTURE0;
    if(GL_TEXTURE31 == position) {
        std::cout << "[Error] [TextureGenerator] Cannot create texture."
                  << "The all slots was filled." << std::endl;
        return nullptr;
    }
    TexturePtr texture(nullptr);
    switch(type) {
        case GL_TEXTURE_1D: texture = TexturePtr(new Texture1D(type, position++)); break;
        case GL_TEXTURE_2D: texture = TexturePtr(new Texture2D(type, position++)); break;
        case GL_TEXTURE_3D: texture = TexturePtr(new Texture3D(type, position++)); break;
        default: return texture;
    }

    for(const auto &param : params) {
        texture->set(param.first, param.second);
    }

    texture->load(imgpath);
    std::cout << "[Info ] [TextureGenerator] The '" << type << "' texture was created from "
              << "'" << imgpath << "' with position " << position << std::endl;
    return texture;
}
