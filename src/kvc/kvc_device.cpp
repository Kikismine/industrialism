#include "kvc_device.hpp"

namespace kvc {

KvcDevice::KvcDevice(VkInstance &instance, const bool _enableValidationLayers, const std::vector<const char*> _validationLayers) : enableValidationLayers(_enableValidationLayers), validationLayers(_validationLayers) {
    pickPhysicalDevice(instance);
    createLogicalDevice();
}

KvcDevice::~KvcDevice() {
    vkDestroyDevice(device, nullptr);
}

// find queue families of a GPU, and check what queue families are available
// using std::optional with std::uint32_t
KvcDevice::QueueFamilyIndices KvcDevice::findQueueFamilies(VkPhysicalDevice device) {
    KvcDevice::QueueFamilyIndices indices;

    // get a list of available queue families of the physical device
    std::uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    // filter and find at least one queue family with VK_QUEUE_GRAPHICS_BIT support
    int i = 0;
    for (const auto& queueFamily: queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        if (indices.isComplete())
            break;

        i++;
    }

    return indices;
}

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
        QueueFamilyIndices indices = findQueueFamilies(candidates.rbegin()->second);

        if (!indices.isComplete())
            throw std::runtime_error("current GPU doesn't have a queue family with VK_QUEUE_GRAPHICS_BIT support");

        std::cout << "GPU that the engine will use: " << getPhysicalDeviceName(candidates.rbegin()->second) << "\n";
        physicalDevice = candidates.rbegin()->second;
    } else {
        throw std::runtime_error("failed to find a suitable GPU(s)");
    }
}

void KvcDevice::createLogicalDevice() {
    KvcDevice::QueueFamilyIndices indices = KvcDevice::findQueueFamilies(physicalDevice);

    // specifying queue creation
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    // vulkan is capable of using queue priority (so i'll do it before some cool algorythm)
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // specifying device features (null for now)
    VkPhysicalDeviceFeatures deviceFeatures{};

    // creating (and specifying) the actual logical device
    VkDeviceCreateInfo createInfo{};
    // add ptrs to queue creation info and device features struct
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    // set enabled layer count and pp enabled layer names for [outdated]
    createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    // instantiate the logical device
    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device");
    } else
        std::cout << "the logical device was successfully created\n";

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

}
