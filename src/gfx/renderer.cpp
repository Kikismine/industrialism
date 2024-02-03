#include "renderer.hpp"
#include "../util/util.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "camera.hpp"

Window window;

Shader vertex_shader;
Shader fragment_shader;
Shader program_shader;

VBO vbo;
VBO ebo;
VAO vao;

Texture grass_top;

float vertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    // Right face
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    // Left face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f
};

static GLuint indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Right face
    8, 9, 10,
    10, 11, 8,
    // Left face
    12, 13, 14,
    14, 15, 12,
    // Top face
    16, 17, 18,
    18, 19, 16,
    // Bottom face
    20, 21, 22,
    22, 23, 20
};

glm::vec3 cubes[] {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

bool glp = false;
float fov = 45.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_x = window.size[0] / 2.0f;
float last_y = window.size[1] / 2.0f;
bool first_mouse = true;

// timing
GLfloat delta_time = 0.0f;
GLfloat last_frame = 0.0f;
GLint counter = 0;

bool fov_change = false;

void _process_input(GLFWwindow *handle) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(handle, true);

    if (glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS)
        camera.keyboard_process(FORWARD, delta_time);
    if (glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS)
        camera.keyboard_process(BACKWARD, delta_time);
    if (glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS)
        camera.keyboard_process(LEFT, delta_time);
    if (glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS)
        camera.keyboard_process(RIGHT, delta_time);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        if (fov == 100) {
            return;
        } else {
            fov_change = true;
            fov += 5;
        }
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        if (fov == 5) {
            return;
        } else {
            fov_change = true;
            fov -= 5;
        }
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        if (glp == false) {
            glp = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else if (glp == true) {
            glp = false;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in) {
    float xpos = static_cast<float>(xpos_in);
    float ypos = static_cast<float>(ypos_in);

    if (first_mouse) {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    float x_offset = xpos - last_x;
    float y_offset = last_y - ypos;

    last_x = xpos;
    last_y = ypos;

    camera.mouse_process(x_offset, y_offset);
}

void _mouse_scroll_process(GLFWwindow* window, double x_offset, double y_offset) {
    camera.mouse_scroll_process(static_cast<float>(y_offset));
}

void draw() {
    glClearColor(0.54, 0.75, 0.91, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grass_top.handle);

    program_shader.use();

    // GLM 3D Transformations

    glm::mat4 projection = glm::perspective(glm::radians(fov), (float) window.size[0] / (float) window.size[1], 0.1f, 100.0f); // projection is a projection matrix (ex. ortographic, perspective, ...)
    program_shader.shader_set_matrix4("projection", projection);

    // init matrix to identity
    glm::mat4 view = camera.get_view_matrix(); // view is a "scene"
    program_shader.shader_set_matrix4("view", view);

    glBindVertexArray(vao.handle);

    for(GLuint i = 0; i < (sizeof(cubes) / sizeof(glm::vec3)); i++)
    {
        glm::mat4 model = glm::mat4(1.0f); // model is a main "camera"
        model = glm::translate(model, cubes[i]);
        /* model = glm::rotate(model, (float)glfwGetTime() * 2 * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); */
        program_shader.shader_set_matrix4("model", model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
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
    texture_create2D(grass_top.handle, GL_REPEAT);
    texture_load(grass_top.width, grass_top.height, grass_top.c_chan, "res/textures/grass_simple_top.png", false);
}

void set_shader_vars() {
    program_shader.shader_set_uniform_int("grass_top", 0);
    program_shader.shader_set_uniform_int("grass_side", 0);
    program_shader.shader_set_uniform_int("grass_bottom", 0);
}

void render_init(GLFWwindow *handle) {
    vertex_objects_init(vbo.handle, vao.handle, ebo.handle, vertices, sizeof(vertices), indices, sizeof(indices));
    shader_init(vertex_shader, fragment_shader, program_shader);
    texture_init();

    program_shader.use();
    set_shader_vars();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(handle))
        render(handle);

    dealloc_elements();
    exit_wgl();
}

void render(GLFWwindow *window) {
    // get per-frame timing
    GLfloat current_frame = camera.get_current_frame();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    counter++;

    // process input
    _process_input(window);

    // render
    draw();

    if (fov_change == true) {
        fov_change = false;
        std::cout << "current fov: " << fov << "\n";
    }

    if (counter >= 60) {
        std::cout << "camera position: " << camera.position.x << ", " << camera.position.y << ", " << camera.position.z << "\n";
        counter = 0;
    }

    // events and swap
    glfwSwapBuffers(window);
    glfwPollEvents();
}
