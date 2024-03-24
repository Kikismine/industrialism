#include "kvc_window.hpp"

namespace kvc {

KvcWindow::KvcWindow(std::uint16_t w, std::uint16_t h, std::string _name) : width{w}, height{h}, name{_name} {
    initWindow();
}

KvcWindow::~KvcWindow() {
    // run these 'end' function on deconstruction
    glfwDestroyWindow(window);
    glfwTerminate();
}

void KvcWindow::initWindow() {
    // glfw initialization and window creation
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

}
