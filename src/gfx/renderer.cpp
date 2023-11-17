#include "renderer.hpp"
#include "../util/util.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"

VBO vbo;
VAO vao;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void _process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void draw() {
    glClearColor(0.54, 0.75, 0.91, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void vertex_objects_init(GLuint &vbo, GLuint &vao, float vertices[], GLsizei vert_size) {
    vbo_create(vbo);
    vao_create(vao);

    vao_bind(true, vao);
    vbo_buffer(vbo, vertices, vert_size);

    vao_vertex_attrib();

    // reset buffer and vertex array
    /* vbo_unbind();
     * vao_bind(false, vao); */
}

void render_init(GLFWwindow *window) {
    vertex_objects_init(vbo.handle, vao.handle, vertices, sizeof(vertices));

    while (!glfwWindowShouldClose(window))
        render(window);
}

void render(GLFWwindow *window) {
    // process input
    _process_input(window);

    // render
    draw();

    // events and swap
    glfwSwapBuffers(window);
    glfwPollEvents();
}
