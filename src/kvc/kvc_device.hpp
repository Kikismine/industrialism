#pragma once

#include <vulkan/vulkan.h>

#include <string>

namespace kvc {

class KvcDevice {
    public:
        KvcDevice(VkInstance &instance);
        ~KvcDevice();

        KvcDevice(const KvcDevice &) = delete;
        KvcDevice &operator=(const KvcDevice &) = delete;

    private:
        void pickPhysicalDevice(VkInstance &instance);
        int rateDeviceSuitability(VkPhysicalDevice device);
        std::string getPhysicalDeviceName(VkPhysicalDevice device);

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};

}
