#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window {
public:
    explicit Window(size_t width, size_t height, const std::string &title);
    ~Window();

    bool isActive() const;

    void update();
    void clear(float r, float g, float b);
    void handleEvents();

    static void onWindowResized(GLFWwindow *, int width, int height);
private:
    GLFWwindow *wnd;
};

#endif // __WINDOW_H__
