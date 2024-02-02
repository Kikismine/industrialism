#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG(msg) log(msg, __LINE__, __FILE__, false)
#define LOG_ERR(msg) log(msg, __LINE__, __FILE__, true)

void log(const char* message, int line, const char* file, bool error);

void exit_wgl();

#endif /* UTIL_HPP */
