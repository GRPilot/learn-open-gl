#include "incs.hpp"
#include "logger.hpp"
#include "window.hpp"
#include "mash.hpp"
#include "templates.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "texturegen.hpp"
#include "texture.hpp"

void onGlfwError(int error, const char *descr) {
    LogE("[GLFW] Code: %d, Description: %s", error, descr);
}

int main() {
    glfwSetErrorCallback(onGlfwError);
    if(!glfwInit()) {
        return 1;
    }

    // Window window({800, 600}, "OpenGL + ImGui | Ravesli lesson 7"); // windowed screen
    Window window(glfwGetPrimaryMonitor(), "OpenGL + ImGui | Ravesli lesson 7"); // fullscreen
    if(!window.isAvtive()) {
        return 2;
    }
    const float scaleCoef = window.height() / static_cast<float>(window.width());
    LogI("[main] scaleCoef coef: %.3f", scaleCoef);

    if(GLenum rc = glewInit(); GL_NO_ERROR != rc) {
        LogE("[GLEW] Cannot initialize GLEW: %u", rc);
        return 3;
    }

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(
        "../resources/shaders/vs.glsl",
        "../resources/shaders/fs.glsl");

    if(!shader->success()) {
        std::shared_ptr<ShaderError> error = shader->getLastError();
        LogE("[main] Cannot create shader: %s", error->what.c_str());
        return error->code;
    }

    TemplateGenerator::Template triangle_template {
        TemplateGenerator::generate(TemplateType::SQUARE, 5)
    };
    Mash triangle(triangle_template.first, triangle_template.second, shader);

    shader->use();
    std::vector<TexturePtr> textures {
        TextureGenerator::gen("../resources/textures/texture_0.jpeg", shader),
        TextureGenerator::gen("../resources/textures/texture_1.png", shader)
    };

    glm::vec4 bgcolor{.3f, .2f, .4f, 1.0f};
    float mix_value = 0.8f;
    int texId = 0;
    float angle = 0.0f;
    float xAngle = 0.0f;
    float yAngle = 0.0f;

    while(window.isAvtive()) {
        window.poll_events();
        window.clear(bgcolor);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); 

        shader->use();
        glm::mat4 transformation = glm::mat4(1.0f);
        transformation = glm::rotate(transformation, angle, glm::vec3{0, 0, 1});
        transformation = glm::rotate(transformation, xAngle, glm::vec3{1, 0, 0});
        transformation = glm::rotate(transformation, yAngle, glm::vec3{0, 1, 0});
        transformation = glm::scale(transformation, glm::vec3{scaleCoef, 1, 0});
        shader->set("transform", transformation);
        shader->set("mix_value", mix_value);
        shader->set("texId", texId);
        shader->unuse();

        textures[texId]->bind();
        triangle.bind();
        triangle.draw();
        triangle.unbind();
        textures[texId]->unbind();

        ImGui::Begin("Settings");
            ImGui::TextWrapped("Shader settings:");
            ImGui::SliderFloat("Texture mix value", &mix_value, 0.0f, 1.0f);
            ImGui::SliderAngle("Rotation", &angle);
            ImGui::SliderAngle("X", &xAngle);
            ImGui::SliderAngle("Y", &yAngle);
            ImGui::Separator();
            ImGui::TextWrapped("Global settings:");
            ImGui::ColorEdit3("Clear color", &bgcolor[0]);
            ImGui::Separator();
            ImGui::TextWrapped("Information:");
            ImGui::TextWrapped("Application average %.3f ms/frame (%.1f FPS)",
                               1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("Textures");
            for(size_t i = 0; i < textures.size(); ++i) {
                ImTextureID id = reinterpret_cast<ImTextureID>(textures[i]->id());
                if(ImGui::ImageButton(id, ImVec2{128, 128}, ImVec2{0, 1}, ImVec2{1, 0})) {
                    LogI("[Main] Update texture id: %zd", i);
                    texId = i;
                }
            }
        ImGui::End();

        Logger::instance().draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.update();
    }
}
