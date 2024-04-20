#include <kvc/kvc_window.hpp>
#include <utility>
#include <stdexcept>

namespace kvc {

KvcWindow::KvcWindow(std::uint16_t w, std::uint16_t h, std::string _name) : width{w}, height{h}, name{std::move(_name)} {
    initWindow();
}

KvcWindow::~KvcWindow() {
    // run these 'end' functions on deconstruction
    glfwDestroyWindow(window);
    glfwTerminate();
}

void KvcWindow::initWindow() {
    // glfw initialization and window creation
    if (!glfwInit())
        throw std::runtime_error("failed to initialize GLFW");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

}
