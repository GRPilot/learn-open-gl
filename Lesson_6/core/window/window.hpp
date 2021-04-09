#ifndef LESSON_6_TEXTURES_WINDOW_HPP
#define LESSON_6_TEXTURES_WINDOW_HPP

class Window;

class WindowCounter {
    friend class Window;
    struct WindowInfo {
        Window *pWin = nullptr;
        size_t id = 0;
        explicit WindowInfo(Window *win);
        bool operator==(size_t other_id) const;
    };

    static std::vector<WindowInfo> list;
    static size_t current_id;

    static void addWindow(Window *win);
    static void removeWindow(Window *win);
    static void currentId(size_t id);
    static size_t currentId();

    static std::vector<WindowInfo>::iterator find(size_t id);
public:
    static Window *activeWindow();
};

class Window {
    const size_t _id;
public:
    using EventHandler = std::function<void(GLFWwindow*)>;
    explicit Window(const Size2f &size, const std::string &title);
    virtual ~Window();

    size_t id() const;
    void show();
    void hide();
    void update();
    void clear(const Color &clr) const;
    virtual void pollEvents();
    bool isActive() const;
    bool isPressed(uint32_t key) const;

    Window &push_event(const EventHandler &handler);

private:
    std::vector<EventHandler> handlers;
    GLFWwindow *wnd;
    bool hidden;

    static void onWindowSizeChanged(GLFWwindow *, int width, int height);
};


#endif //LESSON_6_TEXTURES_WINDOW_HPP
