#include "kvc_instance.hpp"

#include <iostream>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace kvc {

KvcInstance::KvcInstance(std::string _appName, std::vector<std::uint8_t> _appVersion, std::string _engineName, std::vector<std::uint8_t> _engineVersion) : appName{_appName}, engineName{_engineName}, appVersion{_appVersion}, engineVersion{_engineVersion} {
    createInstance();
    setupDebugMessenger();
}

KvcInstance::~KvcInstance() {
    if (enableValidationLayers)
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);

    vkDestroyInstance(instance, nullptr);
}

// checks for available validation layers and compares them to the requested ones
bool KvcInstance::checkValidationLayerSupport() {
    // retrieve a list of available validation layers
    std::uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // list (cout) all the available validation layers
    std::cout << "available validation layers:\n";
    for (const auto& layer: availableLayers)
        std::cout << "\t" << layer.layerName << "\n";
    std::cout << "\n";

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties: availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

// return required list of extensions based on enabled/disabled validation layers
std::vector<const char*> KvcInstance::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}

// needed for debug messenger (valid instance must be created)
void KvcInstance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    // all but the info (verbose)
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    // all types
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    // the callback function pointer
    createInfo.pfnUserCallback = debugCallback;

    // bruh read the khronos wiki page of this
    // createInfo.pUserData = nullptr;
}

// setups debug messenger -> custom validation layers callbacks ([some]? predefined in kvc_instance.hpp)
void KvcInstance::setupDebugMessenger() {
    if (!enableValidationLayers) return;

    // debug messenger creation info
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to setup debug messenger");
    } else
        std::cout << "debug messenger setup completed successfully\n";
}

// creates the vulkan instance, with support for extensions and validation layers
void KvcInstance::createInstance() {
    // check validation layer support, break if needed is/are not present
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available");
    } else if (enableValidationLayers)
        std::cout << "successfully loaded validation layer(s)\n\n";

    // define all the app infos
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(appVersion[0], appVersion[1], appVersion[2]);
    appInfo.pEngineName = engineName.c_str();
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersion[0], engineVersion[1], engineVersion[2]);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    // define the instance creation info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto required_extensions = getRequiredExtensions();

    createInfo.enabledExtensionCount = static_cast<std::uint32_t>(required_extensions.size());
    createInfo.ppEnabledExtensionNames = required_extensions.data();

    // debug util messenger creation
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    // get extension count and extensions vector for listing available extensions
    std::uint32_t _aExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &_aExtensionCount, nullptr);
    std::vector<VkExtensionProperties> _aExtensions(_aExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &_aExtensionCount, _aExtensions.data());

    // list (cout) all the available extensions
    std::cout << "available extensions:\n";
    for (const auto& ext: _aExtensions)
        std::cout << "\t" << ext.extensionName << "\n";
    std::cout << "\n";

    // create the instance (try-catch)
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        throw std::runtime_error("failed to create vulkan instance");
    else
        std::cout << "\ncreated vulkan instance successfully\n";
}

}
