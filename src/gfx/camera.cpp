#include "camera.hpp"
#include "../util/util.hpp"

GLfloat Camera::get_current_frame() {
    return static_cast<float>(glfwGetTime());
}

