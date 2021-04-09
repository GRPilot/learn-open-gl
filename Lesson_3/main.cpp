#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void handleEvent(GLFWwindow *window);
void draw(GLFWwindow *window);
void onWindowResized(GLFWwindow *window, int width, int height);

constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 600;

int main() {
    int status = glfwInit();
    std::cout << "[glfwInit] status: " << (status ? "GLFW_TRUE" : "GLFW_FLASE") << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "LESSON 1", NULL, NULL);
    if(nullptr == window) {
        std::cerr << "[glfwCreateWindow] Cannot initialize window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onWindowResized);

    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[glfwLoadGLLoader] Cannot bind OpenGL functions pointers" << std::endl;
        return -1;
    }

    while(!glfwWindowShouldClose(window)) {
        handleEvent(window);
        draw(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void handleEvent(GLFWwindow *window) {
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void draw(GLFWwindow *window) {
    static float red = 0.5f;
    static float green = 0.1f;
    static float blue = 0.7f;
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void onWindowResized(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
