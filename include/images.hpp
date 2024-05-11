#pragma once

#include "util.hpp"

namespace util {
    void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout current_layout, VkImageLayout new_layout);
}