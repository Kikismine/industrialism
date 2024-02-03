#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../util/util.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in);
void _mouse_scroll_process(GLFWwindow* window, double x_offset, double y_offset);
void render_init(GLFWwindow *window);
void render(GLFWwindow *window);

#endif /* ifndef RENDERER_HPP */
