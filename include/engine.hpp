#pragma once

#include "util.hpp"

extern struct Window {
    GLFWwindow *handle;
    VkExtent2D size{1500, 800};
    std::string title{"vulkan"};
};

class Engine {
public:
    bool is_init;
    int frame_number{0};
    bool r_validation_layers = true;

    // main vulkan variables
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkSurfaceKHR surface;

    // swapchain
    VkSwapchainKHR swapchain;
    VkFormat swapchain_image_format;

    std::vector<VkImage> swapchain_images;
    std::vector<VkImageView> swapchain_image_views;
    VkExtent2D swapchain_extent;

    void init();
    void run();
    void draw();
    void terminate();

private:
    void init_vulkan();
    void init_swapchain();
    void init_commands();
    void init_sync_structures();

    void create_swapchain(std::uint32_t width, std::uint32_t height);
    void destroy_swapchain();
};
