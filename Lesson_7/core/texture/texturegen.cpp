#include "incs.hpp"
#include "logger.hpp"
#include "stb_image.h"

#include "texturegen.hpp"
#include "texture.hpp"
#include "shader.hpp"

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
                LogE("[Texture] Cannot load '%s' image", path.c_str());
                return;
            }
            LogI("[Texture] The '%s' was successfully loaded:", path.c_str());
            LogI("[Texture] Texture width: %d", width);
            LogI("[Texture] Texture height: %d", height);
            LogI("[Texture] Texture channels: %d", nrChannels);
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

//== == == == == == == == == == == =  Textures  = == == == == == == == == == == ==//

class Texture2D : public Texture {
public:
    explicit Texture2D(GLenum type, GLenum position) : Texture(type, position) {}

    TextureError load(const std::string &texFilename) override {
        if(texFilename.empty()) {
            return TextureError::EmptyFilename;
        }

        Img image(texFilename);
        if(!image.valid()) {
            LogW("[Texture] Cannot load source from file '%s'", texFilename.c_str());
            return TextureError::CannotLoadSource;
        }

        glTexImage2D(TYPE, 0, image.getChannels(), image.width, image.height,
                     0, image.getChannels(), GL_UNSIGNED_BYTE, image.source);
        glGenerateMipmap(TYPE);

        return TextureError::NoError;
    }
};

//== == == == == == == == == == = TextureGenerator = == == == == == == == == == ==//

TexturePtr TextureGenerator::gen(const std::string &filename, ShaderPtr shader, GLenum type) {
    Params defaultParams {
        std::make_pair(GL_TEXTURE_WRAP_S, GL_REPEAT),
        std::make_pair(GL_TEXTURE_WRAP_T, GL_REPEAT),
        std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
        std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    };
    return gen(filename, shader, defaultParams, type);
}

TexturePtr TextureGenerator::gen(const std::string &filename, ShaderPtr shader, const Params &params, GLenum type) {
    static GLenum position = GL_TEXTURE0;
    if(GL_TEXTURE31 == position) {
        LogW("[TextureGenerator] Cannot create texture: the all slots was filles");
        return nullptr;
    }

    TexturePtr texture;
    switch(type) {
        case GL_TEXTURE_2D:
            texture = std::make_shared<Texture2D>(type, position);
            break;
        default:
            LogE("[TextureGenerator] Incorrect type");
            return nullptr;
    }

    for(const auto &param : params) {
        texture->set(param.first, param.second);
    }

    TextureError status = texture->load(filename);
    if(TextureError::NoError != status) {
        LogE("[TextureGenerator] The loading was failed: %d",
            static_cast<int>(status));
    }
    int id = position - GL_TEXTURE0;
    LogI("[TextureGenerator] The texture id: %d", id);
    shader->set("sample_" + std::to_string(id), id);
    ++position;
    return texture;
}
