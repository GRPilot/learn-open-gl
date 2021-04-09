#include "platform.h"

#include "window.h"
#include "shader.h"
#include "vertex.h"

struct glfwWrapper {
    ~glfwWrapper() {
        glfwTerminate();
    }
};

using byte_t = unsigned char;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int counter = 0;
    glfwWrapper init;
    Window window(800, 600, "Hello world");

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[ERROR] Cannot load GLAD";
    }

    Shader shader;
    shader.addShader("vertex.vs.glsl");
    shader.addShader("fragment.fs.glsl");
    shader.linkShaderProgram();

    std::vector<Vertex> vertices {
        Vertex{ glm::vec3{ -0.5f, -0.5f,  0.0f }, glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f } },
        Vertex{ glm::vec3{  0.5f, -0.5f,  0.0f }, glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f } },
        Vertex{ glm::vec3{  0.5f,  0.5f,  0.0f }, glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f } },
        Vertex{ glm::vec3{ -0.5f,  0.5f,  0.0f }, glm::vec4{ 0.5f, 0.5f, 0.5f, 0.0f } },
    };
    GLuint indices[] {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO{};
    enum {
        POSITION_VB,
        COLOR_VB,
        BUFFERS_COUNT
    };
    GLuint buffers[BUFFERS_COUNT];
    GLuint EBO{};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(BUFFERS_COUNT, buffers);
    glGenBuffers(1, &EBO);

    std::vector<decltype(vertices.front().position)> positions;
    std::vector<decltype(vertices.front().color)> colors;
    positions.reserve(vertices.size());
    colors.reserve(vertices.size());
    for(size_t i = 0; i < vertices.size(); ++i) {
        positions.push_back(vertices[i].position);
        colors.push_back(vertices[i].color);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), positions.data(), GL_STATIC_DRAW);
    GLint pos_loc = shader.getAttributeLocation("position");
    glEnableVertexAttribArray(pos_loc);
    glVertexAttribPointer(pos_loc, POSITION_COUNT, GL_FLOAT, GL_FALSE,
                          POSITION_SIZE, (GLvoid *)0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[COLOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), colors.data(), GL_STATIC_DRAW);
    GLint clr_loc = shader.getAttributeLocation("color");
    glEnableVertexAttribArray(clr_loc);
    glVertexAttribPointer(clr_loc, COLOR_COUNT, GL_FLOAT, GL_FALSE,
                          COLOR_SIZE, (GLvoid *)(0));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    // Раскомментируйте следующую строку для отрисовки полигонов в режиме каркаса
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.use();
    glBindVertexArray(VAO);
    while(window.isActive()) {
        window.handleEvents();
        window.clear(0.3f, 0.1f, 0.5f);

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL);

        window.update();
    }
}
