#pragma once

#include <util.hpp>
#include <functional>

class Input {
public:
    std::array<std::function<void()>, GLFW_KEY_LAST+1> key_actions;

    void init();
    void handle(int key);
    // actions
    std::function<void()> on_quit;
    std::function<void()> on_red_higher;
    std::function<void()> on_red_lower;

private:
};