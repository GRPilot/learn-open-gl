//
// Created by gollan on 13.03.2021.
//
#include "deps.hpp"
#include "randomgenerator.hpp"

#include "window.hpp"

#define RETURN_IF_WINDOW_NULL \
    if(nullptr == wnd) return
#define RETURN_IF_WINDOW_HIDDEN \
    if(hidden) return


Window::Window(const Size2f &size, const std::string &title)
    : _id(RandomGenerator::instance().ulnext()),
      wnd(glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr)),
      hidden(true) {
    if(nullptr == wnd) {
        std::cerr << "[ERROR][Window] Cannot initialize window '" << title << "'" << std::endl;
        return;
    }
    WindowCounter::addWindow(this);
    glfwSetFramebufferSizeCallback(wnd, Window::onWindowSizeChanged);
    std::cout << "[Info ] [Window] Window was successfully created. It's full ID is " << _id << std::endl;
}

Window::~Window() {
    WindowCounter::removeWindow(this);
    RETURN_IF_WINDOW_NULL;
    glfwDestroyWindow(wnd);
}

void Window::show() {
    RETURN_IF_WINDOW_NULL;
    glfwMakeContextCurrent(wnd);
    glfwShowWindow(wnd);
    WindowCounter::currentId(this->id());
    hidden = false;
}

void Window::hide() {
    RETURN_IF_WINDOW_NULL;
    RETURN_IF_WINDOW_HIDDEN;
    glfwHideWindow(wnd);
    hidden = true;
}

void Window::update() {
    RETURN_IF_WINDOW_NULL;
    RETURN_IF_WINDOW_HIDDEN;
    glfwSwapBuffers(wnd);
}

void Window::pollEvents() {
    RETURN_IF_WINDOW_NULL;
    RETURN_IF_WINDOW_HIDDEN;

    for(const auto &handler : handlers) {
        handler(wnd);
    }
    glfwPollEvents();
}

void Window::onWindowSizeChanged(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}

bool Window::isActive() const {
    return nullptr != wnd && !glfwWindowShouldClose(wnd);
}

void Window::clear(const Color &clr) const {
    glClearColor(clr.r, clr.g, clr.b, clr.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

size_t Window::id() const {
    return _id;
}

Window &Window::push_event(const Window::EventHandler &handler) {
    handlers.push_back(handler);
    std::cout << "[Info ] [Window#" << (_id % 100) << "] Event was attached" << std::endl;
    return *this;
}

bool Window::isPressed(uint32_t key) const {
//    static int prevState = 0;
//    static uint32_t prevKey = 0;
//    int curState = glfwGetKey(wnd, key);
//    if(GLFW_PRESS == prevState && GLFW_RELEASE == curState && prevKey == key) {
//        return true;
//    }
//    prevState = curState;
//    prevKey = key;
//
//    return false;
    return GLFW_PRESS == glfwGetKey(wnd, key);
}

//=============================== WindowCounter ===============================//

std::vector<WindowCounter::WindowInfo> WindowCounter::list = std::vector<WindowCounter::WindowInfo>();
size_t WindowCounter::current_id = 0;

WindowCounter::WindowInfo::WindowInfo(Window *win) : pWin(win) {
    if(nullptr != pWin) {
        id = pWin->id();
    }
}

bool WindowCounter::WindowInfo::operator==(size_t other_id) const {
    return id == other_id;
}

void WindowCounter::addWindow(Window *win) {
    if(nullptr == win) {
        return;
    }

    for(const auto &w : WindowCounter::list) {
        if(w.id == win->id()) {
            return;
        }
    }
    WindowCounter::list.emplace_back(win);
}

void WindowCounter::removeWindow(Window *win) {
    if(nullptr == win) {
        return;
    }

    auto found = find(win->id());
    if(list.end() == found) {
        return;
    }
    list.erase(found);
}

void WindowCounter::currentId(size_t id) {
    current_id = id;
}

size_t WindowCounter::currentId() {
    return current_id;
}

Window *WindowCounter::activeWindow() {
    return find(current_id)->pWin;
}

std::vector<WindowCounter::WindowInfo>::iterator WindowCounter::find(size_t id) {
    return std::find(list.begin(), list.end(), id);
}
