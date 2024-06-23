#pragma once

#include <util.hpp>
#include "logger.hpp"

struct DestroyGLFWwindow {
    void operator()(GLFWwindow* ptr) {
        glfwDestroyWindow(ptr);
    }
};

typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowHandle;

class Window {
public:
    Window(int width, int height, std::string _title) noexcept;

    GLFWwindowHandle handle;
    Extent2D size{};
    std::string title;

    static void init_glfw();
    void init_window();
    static void init_glad();
};
