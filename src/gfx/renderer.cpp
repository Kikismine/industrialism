#include "renderer.hpp"
#include "../util/util.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"

Shader vertex_shader;
Shader fragment_shader;
Shader program_shader;

VBO vbo;
VBO ebo;
VAO vao;

static float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

static GLuint indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

bool glp_on = false;

void _process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (glp_on == false) {
            glp_on = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (glp_on == true) {
            glp_on = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void draw() {
    glClearColor(0.54, 0.75, 0.91, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_shader.shader);

    glBindVertexArray(vao.handle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void dealloc_elements() {
    glDeleteVertexArrays(1, &vao.handle);
    glDeleteBuffers(1, &vbo.handle);
    glDeleteBuffers(1, &ebo.handle);
    glDeleteProgram(program_shader.shader);
}

void vertex_objects_init(GLuint &vbo, GLuint &vao, GLuint &ebo, float vertices[], GLsizei v_size, GLuint indices[], GLsizei i_size) {
    vbo_create(vbo);
    vbo_create(ebo);
    vao_create(vao);

    vao_bind(true, vao);
    vbo_buffer(vbo, vertices, v_size);
    ebo_buffer(ebo, indices, i_size);

    vao_vertex_attrib();

    // reset buffer and vertex array
    /* vbo_unbind(); */
    vao_bind(false, vao);
}

void shader_init(Shader &vertex, Shader &fragment, Shader &program) {
    vertex.path = "res/shaders/vertex.vs";
    fragment.path = "res/shaders/fragment.fs";
    vertex.type = VERTEX_TYPE;
    fragment.type = FRAGMENT_TYPE;

    shader_get_source(vertex.path, vertex.content);
    shader_get_source(fragment.path, fragment.content);

    shader_create(vertex.shader, vertex.content, vertex.type);
    shader_create(fragment.shader, fragment.content, fragment.type);

    shader_program_init(program.shader, vertex.shader, fragment.shader);

    glDeleteShader(vertex.shader);
    glDeleteShader(fragment.shader);
}

void render_init(GLFWwindow *window) {
    vertex_objects_init(vbo.handle, vao.handle, ebo.handle, vertices, sizeof(vertices), indices, sizeof(indices));
    shader_init(vertex_shader, fragment_shader, program_shader);

    while (!glfwWindowShouldClose(window))
        render(window);

    dealloc_elements();
    exit_wgl();
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
