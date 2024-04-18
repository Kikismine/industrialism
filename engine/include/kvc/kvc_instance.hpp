#pragma once

#include "kvc_util.hpp"

namespace kvc {

class KvcInstance {
    public:
        KvcInstance(std::string _appName, std::vector<std::uint8_t> _appVersion, std::string _engineName, std::vector<std::uint8_t> _engineVersion);
        ~KvcInstance();

        KvcInstance(const KvcInstance&) = delete;
        KvcInstance &operator=(const KvcInstance&) = delete;

        VkInstance instance{};

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        // check for NDEBUG (c++ standard, not debug) -> enable/disable validation layers
        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif

    private:
        void createInstance();
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void setupDebugMessenger();
        bool checkValidationLayerSupport();
        [[nodiscard]] std::vector<const char*> getRequiredExtensions() const;

        VkDebugUtilsMessengerEXT debugMessenger{};
        std::string appName, engineName;
        std::vector<std::uint8_t> appVersion;
        std::vector<std::uint8_t> engineVersion;

        static const bool _lVerbose = false;
        static const bool _lInfo = false;
        static const bool _lWarning = true;
        static const bool _lError = true;
        static const bool _lBits = false;

        // validation layers custom debug callback implementation
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            [[maybe_unused]] void* pUserData) {
            // check if the message is more important than ...
            // if (messageSeverity >= ...) {}

            // for every layer category (severity), type different pre-text
            // and type it just if the category bool is 'checked'
            switch (messageSeverity) {
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                    if (_lVerbose) std::cout << "[VERBOSE]: " << pCallbackData->pMessage << "\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                    if (_lInfo) std::cout << "[INFO]: " << pCallbackData->pMessage << "\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    if (_lWarning) std::cout << "[WARNING]: " << pCallbackData->pMessage << "\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                    if (_lError) std::cerr << "[ERROR]: " << pCallbackData->pMessage << std::endl;
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
                    if (_lBits) std::cout << "[FLAG BITS (kvc_instance)]: " << pCallbackData->pMessage << "\n";
                    break;
                default:
                    std::cout << "[SEVERITY NOT FOUND (kvc_instance)]: " << pCallbackData->pMessage << "\n";
                    break;
            }

            return VK_FALSE;
        }

        // debug utils messenger creation proxy (it's extension fun. so it's not pre made)
        static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
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
