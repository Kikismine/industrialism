#include <engine.hpp>

Engine engine;

int main() {
    try {
        engine.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}