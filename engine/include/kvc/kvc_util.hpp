#pragma once

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>
#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <map>
#include <utility>
#include <optional>
