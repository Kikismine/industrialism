#include <kvc/kvc_surface.hpp>

namespace kvc {

KvcSurface::KvcSurface(VkInstance instance, GLFWwindow* window) {
    _instance = instance;
    createSurface(window);
}

KvcSurface::~KvcSurface() {
    vkDestroySurfaceKHR(_instance, surface, nullptr);
}

void KvcSurface::createSurface(GLFWwindow *window) {
    // create the window surface (try-catch)
    if (glfwCreateWindowSurface(_instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    } else
        std::cout << "created window surface successfully\n";
}

}