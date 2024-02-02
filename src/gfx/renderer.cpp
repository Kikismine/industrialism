#include "renderer.hpp"
#include "../util/util.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "texture.hpp"
#include "window.hpp"

Window window;

Shader vertex_shader;
Shader fragment_shader;
Shader program_shader;

VBO vbo;
VBO ebo;
VAO vao;

Texture wall;
Texture spider;

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
};

static GLuint indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

bool glp = false;
bool rgb = false;
bool cvr = false;

void _process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (glp == false) {
            glp = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (glp == true) {
            glp = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (rgb == false) {
            rgb = true;
            program_shader.shader_set_uniform_bool("rgb", 1);
        } else if (rgb == true) {
            rgb = false;
            program_shader.shader_set_uniform_bool("rgb", 0);
        }
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        if (cvr == false) {
            cvr = true;
            program_shader.shader_set_uniform_bool("cvr", 1);
        } else if (cvr == true) {
            cvr = false;
            program_shader.shader_set_uniform_bool("cvr", 0);
        }
    }
}

void draw() {
    glClearColor(0.54, 0.75, 0.91, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wall.handle);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, spider.handle);

    program_shader.use();

    // GLM 3D Transformations

    // init matrixes to identity
    glm::mat4 model = glm::mat4(1.0f); // model is a main "camera"
    glm::mat4 view = glm::mat4(1.0f); // view is a "scene"
    glm::mat4 projection = glm::mat4(1.0f); // projection is a projection matrix (ex. ortographic, perspective, ...)

    /* model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate everything (main "camera" rotation) */
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // move the "scene" away from us (to -z axis [right handed system])
    projection = glm::perspective(glm::radians(45.0f), (float) window.size[0] / (float) window.size[1], 0.1f, 100.0f);

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    // pass the matrixes to the shader
    program_shader.shader_set_matrix4("model", model);
    program_shader.shader_set_matrix4("view", view);
    program_shader.shader_set_matrix4("projection", projection);

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

void texture_init() {
    texture_create2D(wall.handle, GL_REPEAT);
    texture_load(wall.width, wall.height, wall.c_chan, "res/textures/grass_concept.png", false);

    texture_create2D(spider.handle, GL_REPEAT);
    texture_load(spider.width, spider.height, spider.c_chan, "res/textures/spider.png", true);
}

void set_shader_vars() {
    program_shader.shader_set_uniform_int("spider", 1);
    program_shader.shader_set_uniform_int("wall", 0);
}

void render_init(GLFWwindow *window) {
    vertex_objects_init(vbo.handle, vao.handle, ebo.handle, vertices, sizeof(vertices), indices, sizeof(indices));
    shader_init(vertex_shader, fragment_shader, program_shader);
    texture_init();

    program_shader.use();
    set_shader_vars();

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
