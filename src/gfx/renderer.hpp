#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../util/util.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void render_init(GLFWwindow *window);
void render(GLFWwindow *window);

#endif /* ifndef RENDERER_HPP */
