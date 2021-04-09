#include "deps.hpp"
#include "Window.hpp"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window(800, 600, "OpenGL | Ravesli - Lesson 5: Shaders");

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[ERROR] Failed to load glad" << std::endl;
        return -1;
    }

    while(window.isOpen()) {
        window.handleEvent();
        window.clear(.3, .5, .2);

        window.update();
    }
}
