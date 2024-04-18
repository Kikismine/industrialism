#pragma once

#include "kvc_util.hpp"

namespace kvc {

class KvcDevice {
    public:
        KvcDevice(VkInstance &instance, const bool _enableValidationLayers, const std::vector<const char*> validationLayers);
        ~KvcDevice();

        KvcDevice(const KvcDevice &) = delete;
        KvcDevice &operator=(const KvcDevice &) = delete;

        struct QueueFamilyIndices {
            std::optional<std::uint32_t> graphicsFamily;

            // check if the search is completed
            bool isComplete() {
                return graphicsFamily.has_value();
            }
        };

    private:
        // device(s) related functions and variables
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;

        const bool enableValidationLayers;
        const std::vector<const char*> validationLayers;

        void pickPhysicalDevice(VkInstance &instance);
        int rateDeviceSuitability(VkPhysicalDevice device);
        std::string getPhysicalDeviceName(VkPhysicalDevice device);

        void createLogicalDevice();

        // queue(s) related functions and variables
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

}
