#pragma once

#include <util.hpp>
#include <logger.hpp>
#include <input.hpp>

struct DestroyGLFWwindow {
    void operator()(GLFWwindow* ptr) {
        glfwDestroyWindow(ptr);
    }
};

typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> GLFWwindowHandle;

class Window {
public:
    Window(int width, int height, std::string _title) noexcept;

    Input* input;
    Logger* logger = Logger::get_logger();

    GLFWwindowHandle handle;
    Extent2D size{};
    std::string title;

    void init_glfw();
    void init_window();
    void init_glad();

    // actions
    void quit();
};
