#include "platform.h"

#include "window.h"

Window::Window(size_t width, size_t heigth, const std::string &title)
    : wnd(glfwCreateWindow(width, heigth, title.c_str(), NULL, NULL)) {
    if(NULL == wnd) {
        return;
    }

    glfwMakeContextCurrent(wnd);
    glfwSetFramebufferSizeCallback(wnd, Window::onWindowResized);
}
Window::~Window() {
    if(NULL != wnd) {
        glfwDestroyWindow(wnd);
        wnd = NULL;
    }
}

bool Window::isActive() const {
    if(NULL == wnd) {
        return false;
    }

    return !glfwWindowShouldClose(wnd);
}

void Window::update() {
    glfwSwapBuffers(wnd);
}
void Window::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Window::handleEvents() {
    if(GLFW_PRESS == glfwGetKey(wnd, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(wnd, GLFW_TRUE);
    }
    glfwPollEvents();
}

void Window::onWindowResized(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}

