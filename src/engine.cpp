#include "engine.hpp"

namespace kvc {

void Engine::run() {
    while (!kvcWindow.shouldClose()) {
        glfwPollEvents();
    }
}

}
