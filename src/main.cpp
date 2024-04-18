#include "engine.hpp"

#include <iostream>

int main() {
    kvc::Engine engine{};

    // try to run the engine
    try {
        engine.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
