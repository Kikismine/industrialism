#include "renderer.hpp"
#include "../util/util.hpp" 

<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
void render(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void draw() {
    glClearColor(0.54, 0.75, 0.91, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // process input
        process_input(window);

        // render
        draw();

        // events and swap
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
