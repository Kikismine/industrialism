#include "renderer.hpp"
#include "../util/util.hpp" 

void render(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
