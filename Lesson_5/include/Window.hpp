#pragma once

class Window {
public:
    Window(size_t width, size_t height, const std::string &title);
    ~Window();

    bool isOpen() const;
    void update();
    void clear(GLfloat red, GLfloat green, GLfloat blue);
    void handleEvent();

    static void onWindowSizeChanged(GLFWwindow *, int width, int height);
private:
    GLFWwindow *wnd;
};
