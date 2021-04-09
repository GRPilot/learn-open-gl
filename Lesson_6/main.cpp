#include "deps.hpp"

#include "window.hpp"
#include "mash.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "texture.hpp"
#include "texturegen.hpp"

int main() {
    INIT_GLFW3;

    Window window(Size2f{800, 600}, "OpenGL | Ravesli. Lesson 6 - Textures");
    window.show();

    glfwSetErrorCallback([](int errcode, const char *errstr){
        std::cerr << "[Error] [GLFW] Code: " << errcode << "; error: " << errstr << std::endl;
    });

    if(!INIT_GLAD) {
        std::cerr << "Cannot initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    std::shared_ptr<Shader> shader{ std::make_shared<Shader>(
            "../resources/shaders/vs.glsl",
            "../resources/shaders/fs.glsl"
    )};

    window
        .push_event([&window](GLFWwindow *wnd){
            if(window.isPressed(GLFW_KEY_ESCAPE)) {
                glfwSetWindowShouldClose(wnd, GLFW_TRUE);
            }
        })
        .push_event([&window, &shader](GLFWwindow *wnd){
            if(window.isPressed(GLFW_KEY_1)) {
                std::cout << "[Info ] [Window] turn color on" << std::endl;
                shader->set("useColor", true);
                return;
            }
            if(window.isPressed(GLFW_KEY_2)) {
                std::cout << "[Info ] [Window] turn color off" << std::endl;
                shader->set("useColor", false);
                return;
            }
        })
        .push_event([&window, &shader](GLFWwindow *) {
            if(window.isPressed(GLFW_KEY_3)) {
                std::cout << "[Info ] [Window] turn texture on" << std::endl;
                shader->set("useTexture", true);
                return;
            }
            if(window.isPressed(GLFW_KEY_4)) {
                std::cout << "[Info ] [Window] turn texture off" << std::endl;
                shader->set("useTexture", false);
                return;
            }
        })
        .push_event([&window, &shader](GLFWwindow *){
            if(window.isPressed(GLFW_KEY_5)) {
                shader->set("hflip", true);
                return;
            }
            if(window.isPressed(GLFW_KEY_6)) {
                shader->set("hflip", false);
                return;
            }
            if(window.isPressed(GLFW_KEY_7)) {
                shader->set("vflip", true);
                return;
            }
            if(window.isPressed(GLFW_KEY_8)) {
                shader->set("vflip", false);
                return;
            }
        })
        .push_event([&window, &shader](GLFWwindow *){
            static float inter_coef = 0.5f;
            if(window.isPressed(GLFW_KEY_UP)) {
                if(inter_coef > 1.0f) {
                    return;
                }
                inter_coef += 0.01f;
                shader->set("inter_value", inter_coef);
                return;
            }
            if(window.isPressed(GLFW_KEY_DOWN)) {
                if(inter_coef < 0.0f) {
                    return;
                }
                inter_coef -= 0.01f;
                shader->set("inter_value", inter_coef);
                return;
            }
        });

    using namespace glm;

    float alpha = 1.0f;
    vec4 red{ 1.0f, 0.0f, 0.0f, alpha };
    vec4 green{ 0.0f, 1.0f, 0.0f, alpha };
    vec4 blue{ 0.0f, 0.0f, 1.0f, alpha };
    vec4 black{ 0.0f, 0.0f, 0.0f, alpha };

    std::vector<Vertex> verts {
        Vertex{ glm::vec3{ -0.5f, -0.5f, 0.f }, red,   glm::vec2{ 0, 0 } },
        Vertex{ glm::vec3{  0.5f, -0.5f, 0.f }, green, glm::vec2{ 1, 0 } },
        Vertex{ glm::vec3{  0.5f,  0.5f, 0.f }, blue,  glm::vec2{ 1, 1 } },
        Vertex{ glm::vec3{ -0.5f,  0.5f, 0.f }, black, glm::vec2{ 0, 1 } },
    };
    Vertices vertices{
        verts,
        { 0, 1, 2, 0, 2, 3 }
    };

    Mash mash(vertices, shader);

    TextureGenerator::ParamType params{
        std::make_pair(GL_TEXTURE_WRAP_S, GL_REPEAT),
        std::make_pair(GL_TEXTURE_WRAP_T, GL_REPEAT),
        std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
        std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    };

    const std::string textures_path = "../resources/textures";
    TexturePtr container_texture{
        TextureGenerator::generate(GL_TEXTURE_2D, textures_path + "/container.jpg", params)
    };
    TexturePtr smile_texture{
        TextureGenerator::generate(GL_TEXTURE_2D, textures_path + "/smile.png", params)
    };

    std::vector<TexturePtr> usedTextures;
    shader->use();
    if(nullptr != container_texture) {
        usedTextures.push_back(container_texture);
        shader->set("texture0", 0);
    }
    if(nullptr != smile_texture) {
        usedTextures.push_back(smile_texture);
        shader->set("texture1", 1);
    }

    while(window.isActive()) {
        window.pollEvents();
        window.clear(Color{0.3f, 0.1f, 0.3f, 0.5f});

        for(auto texture : usedTextures) {
            texture->bind();
        }
        shader->use();
        mash.draw();

        window.update();
    }
}
