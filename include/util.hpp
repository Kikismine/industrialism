#pragma once

// glfw&opengl
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// cpp libs
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <cstdio>
#include <filesystem>

typedef struct Extent2D {
    uint32_t width;
    uint32_t height;
} Extent2D;