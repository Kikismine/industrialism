#include <engine.hpp>

int main() {
    Engine engine;

    engine.init();
    engine.run();
    engine.terminate();

    return 0;
}