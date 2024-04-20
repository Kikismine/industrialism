#pragma once

#include "kvc_util.hpp"

namespace kvc {

class KvcSurface {
public:
    KvcSurface(VkInstance instance, GLFWwindow* window);
    ~KvcSurface();

    KvcSurface(const KvcSurface&) = delete;
    KvcSurface &operator=(const KvcSurface&) = delete;

    VkSurfaceKHR surface{};

private:
    VkInstance _instance;

    void createSurface(GLFWwindow *window);
};

}