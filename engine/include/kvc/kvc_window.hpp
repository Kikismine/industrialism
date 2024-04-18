#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <cstdint>

namespace kvc {

class KvcWindow {
    public:
        KvcWindow(std::uint16_t w, std::uint16_t h, std::string _name);
        ~KvcWindow();

        KvcWindow(const KvcWindow &) = delete;
        KvcWindow &operator=(const KvcWindow &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }

    private:
        void initWindow();

        std::uint16_t width, height;
        std::string name;
        GLFWwindow *window{};
};

}
