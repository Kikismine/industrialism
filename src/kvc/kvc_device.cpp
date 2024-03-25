#include "kvc_device.hpp"

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

namespace kvc {

KvcDevice::KvcDevice(VkInstance &instance) {
    pickPhysicalDevice(instance);
}

KvcDevice::~KvcDevice() {}

// rate physical device by it's suitability
int KvcDevice::rateDeviceSuitability(VkPhysicalDevice device) {
    // get physical device properties (vulkan version, ...)
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    // get physical device features (texture compression, ...)
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    int score = 0;

    // discrete gpus have performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    // maximum possible size of texture + image quality
    score += deviceProperties.limits.maxImageDimension2D;

    if (!deviceFeatures.geometryShader)
        return 0;

    return score;
}

std::string KvcDevice::getPhysicalDeviceName(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    return deviceProperties.deviceName;
}

// find and pick a best suiting GPU with Vulkan support
void KvcDevice::pickPhysicalDevice(VkInstance &instance) {
    // list all devices with Vulkan support
    std::uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPU(s) with Vulkan support");
    } else
        std::cout << "GPU(s) with Vulkan support was/were found\n";

    // allocate array for all VkPhysicalDevice handles
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // list (cout) all found devices
    std::cout << "available GPU(s):\n";
    for (auto& device: devices)
        std::cout << "\t" << device << "\n";
    std::cout << "\n";

    // use an ordered map to automatically sort gpu candidates by score
    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& device: devices) {
        int score = rateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    // check if first candidate is even suitable
    if (candidates.rbegin()->first > 0) {
        std::cout << "GPU that the engine will use: " << getPhysicalDeviceName(candidates.rbegin()->second);
        physicalDevice = candidates.rbegin()->second;
    } else {
        throw std::runtime_error("failed to find a suitable GPU(s)");
    }
}

}
