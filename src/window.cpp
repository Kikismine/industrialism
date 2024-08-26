#include <utility>
#include <window.hpp>
#include <logger.hpp>

Input *_input;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // this just works for the GLFW_PRESS option (for now)
    _input->init();
    if (action == GLFW_PRESS)
        _input->handle(key);
}

Window::Window(int width, int height, std::string _title) noexcept {
    size.width = width;
    size.height = height;
    title = std::move(_title);

    input = new Input();
    _input = input;
}

void Window::init_glfw() {
    if (!glfwInit())
        logger->throw_err("An error has occurred while initializing GLFW");
    else
        logger->println("GLFW initialized successfully");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // resizable window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Window::init_window() {
    handle = GLFWwindowHandle(glfwCreateWindow((int) size.width, (int) size.height, title.c_str(), nullptr, nullptr));

    if (handle == nullptr)
        logger->throw_err("An error has occurred while creating GLFW window");
    else
        logger->println("GLFW window created successfully");

    glfwSetKeyCallback(handle.get(), key_callback);
    glfwMakeContextCurrent(handle.get());
}

void Window::init_glad() {
    int version = gladLoadGL(glfwGetProcAddress);
    if (!version)
        logger->throw_err("An error has occurred while loading an OpenGL context");
    else
        logger->println("OpenGL context using GLAD created successfully");

    std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
}

// actions
void Window::quit() {
    glfwDestroyWindow(handle.get());
}