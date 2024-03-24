#pragma once

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

namespace kvc {

class KvcInstance {
    public:
        KvcInstance(std::string _appName, std::vector<std::uint8_t> _appVersion, std::string _engineName, std::vector<std::uint8_t> _engineVersion);
        ~KvcInstance();

        KvcInstance(const KvcInstance&) = delete;
        KvcInstance &operator=(const KvcInstance&) = delete;

    private:
        void createInstance();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void setupDebugMessenger();
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        // check for NDEBUG (c++ standard, not debug) -> enable/disable validation layers
        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        std::string appName, engineName;
        std::vector<std::uint8_t> appVersion;
        std::vector<std::uint8_t> engineVersion;

        // validation layers custom debug callback implementation
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
            // check if message is more important then ...
            // if (messageSeverity >= ...) {}

            bool vnInfoDebug = true;

            if (!vnInfoDebug && messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
                std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
            else if (vnInfoDebug)
                std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }

        // debug utils messenger creation proxy (it's extension fun. so no premade)
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

            if (func != nullptr)
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            else
                return VK_ERROR_EXTENSION_NOT_PRESENT;
        }

        // debug utils messenger deletion proxy
        static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }
};

}
