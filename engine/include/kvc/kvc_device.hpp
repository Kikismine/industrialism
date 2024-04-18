#pragma once

#include "kvc_util.hpp"

namespace kvc {

class KvcDevice {
    public:
        KvcDevice(VkInstance &instance, bool _enableValidationLayers, const std::vector<const char*>& validationLayers);
        ~KvcDevice();

        KvcDevice(const KvcDevice &) = delete;
        KvcDevice &operator=(const KvcDevice &) = delete;

        struct QueueFamilyIndices {
            std::optional<std::uint32_t> graphicsFamily;

            // check if the search is completed
            [[nodiscard]] bool isComplete() const {
                return graphicsFamily.has_value();
            }
        };

    private:
        // device(s) related functions and variables
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device{};
        VkQueue graphicsQueue{};

        const bool enableValidationLayers;
        const std::vector<const char*> validationLayers;

        void pickPhysicalDevice(VkInstance &instance);
        static int rateDeviceSuitability(VkPhysicalDevice device);
        static std::string getPhysicalDeviceName(VkPhysicalDevice device);

        void createLogicalDevice();

        // queue(s) related functions and variables
        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

}
