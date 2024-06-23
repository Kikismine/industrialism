#include <engine.hpp>

void Engine::run() {
    window->init_glfw();
    window->init_window();
    window->init_glad();
    loop();
    terminate();
}

void Engine::loop() {
    glViewport(0, 0, window->size.width, window->size.height);

    while (!glfwWindowShouldClose(window->handle.get())) {
//        renderer->render();
//        input->check_input(this, main_key_input);

        glfwSwapBuffers(window->handle.get());
        glfwPollEvents();
    }
}

void Engine::terminate() {

}