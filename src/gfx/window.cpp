#include "window.hpp"
#include "../util/util.hpp"
#include "renderer.hpp"
#include "camera.hpp"

Window wndw;

void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void _error_callback(int code, const char* description) {
    std::cerr << "GLFW error " << code << ":" << description << "\n";
}

void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    key_callback(window, key, scancode, action, mods);
}

void _mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    mouse_callback(window, xpos, ypos);
}

void _scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    _mouse_scroll_process(window, x_offset, y_offset);
}

void Window::init_glfw(GLuint major, GLuint minor) {

    // check if glfwInit() is loaded
    if (!glfwInit()) {
        LOG_ERR("An error has occured while initializing GLFW");
        exit(-1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (Window::is_apple) {
       glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
}

void Window::create_window() {
    init_glfw(3, 3);

    const char* c_title = wndw.title.c_str();
    wndw.handle = glfwCreateWindow(wndw.size[0], wndw.size[1], c_title, NULL, NULL);

    /* std::cout << wndw.handle << "\n"; */

    if (wndw.handle == NULL) {
        LOG_ERR("An error has occured while creating GLFW window");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(wndw.handle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERR("An error has occured while initializing GLAD");
        glfwTerminate();
        exit(-1);
    }

    glfwSetInputMode(wndw.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetErrorCallback(_error_callback);
    glfwSetFramebufferSizeCallback(wndw.handle, _framebuffer_size_callback);
    glfwSetKeyCallback(wndw.handle, _key_callback);
    glfwSetCursorPosCallback(wndw.handle, _mouse_callback);
    glfwSetScrollCallback(wndw.handle, _scroll_callback);

    render_init(wndw.handle);
}

