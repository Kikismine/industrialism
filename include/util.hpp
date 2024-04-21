#pragma once

// vulkan
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <VkBootstrap.h>

// cpp libs
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <cstdio>
#include <filesystem>

#define VK_CHECK(x) do { VkResult err = x; if (err) { std::cerr << "vulkan err: " << err << "\n"; abort(); } } while (0)