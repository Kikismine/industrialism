#include <engine.hpp>

void Engine::init_input() {
    window->input->on_quit = [&] { quit(); };
    window->input->on_red_higher = [&] { red_higher(); };
    window->input->on_red_lower = [&] { red_lower(); };
}

// actions
void Engine::quit() {
    glfwSetWindowShouldClose(window->handle.get(), true);
}

void Engine::red_higher() {
    renderer->red += .10f;
}

void Engine::red_lower() {
    renderer->red -= .10f;
}

void Engine::run() {
    window->init_glfw();
    window->init_window();
    window->init_glad();

    init_input();

    loop();
    terminate();
}

void Engine::loop() {
    glViewport(0, 0, (int) window->size.width, (int) window->size.height);

    while (!glfwWindowShouldClose(window->handle.get())) {
        renderer->render();

        glfwSwapBuffers(window->handle.get());
        glfwPollEvents();
    }
}

void Engine::terminate() {

}