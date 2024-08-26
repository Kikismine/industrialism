#include <input.hpp>

void Input::init() {
    key_actions.at(GLFW_KEY_ESCAPE) = on_quit;
    key_actions.at(GLFW_KEY_UP) = on_red_higher;
    key_actions.at(GLFW_KEY_DOWN) = on_red_lower;
}

void Input::handle(int key) {
    key_actions[key]();
}