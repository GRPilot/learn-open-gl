#include "deps.hpp"

#include "Window.hpp"

Window::Window(size_t width, size_t height, const std::string &title) 
    : wnd(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)){

    if(nullptr == wnd) {
        return;
    }
    glfwMakeContextCurrent(wnd);
    glfwSetFramebufferSizeCallback(wnd, Window::onWindowSizeChanged);
}

Window::~Window() {
    if(nullptr != wnd) {
        glfwDestroyWindow(wnd);
    }
}

bool Window::isOpen() const {
    return (nullptr != wnd) && (!glfwWindowShouldClose(wnd));
}

void Window::update() {
    glfwSwapBuffers(wnd);
}

void Window::clear(GLfloat red, GLfloat green, GLfloat blue) {
    glClearColor(red, green, blue, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::handleEvent() {
    if(GLFW_PRESS == glfwGetKey(wnd, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(wnd, true);
    }
    glfwPollEvents();
}

void Window::onWindowSizeChanged(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}

