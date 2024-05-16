#include <engine.hpp>
#include <algorithm>

void Engine::init_window() {
    if (!glfwInit())
        logger->throw_err("glfw initialization error");
    else
        logger->println("glfw initialized successfully");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window.handle = glfwCreateWindow((int) window.size.width, (int) window.size.height, window.title.c_str(), nullptr, nullptr);

    if (window.handle == nullptr)
        logger->throw_err("glfw window creation error");
    else
        logger->println("glfw window created successfully");

}

void Engine::create_instance() {
    // type the `app_info` properties
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "vulkan engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "vulkan engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    // type the `create_info` properties
    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;

    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    create_info.enabledExtensionCount = glfw_extension_count;
    create_info.ppEnabledExtensionNames = glfw_extensions;

    create_info.enabledLayerCount = 0;

    // get extension count to `extension_count`
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // create a vector `extensions` that stores all the extensions based on `extension_count`
    std::vector<VkExtensionProperties> extensions(extension_count);

    // query the extension details
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

    // list all the extension names
    logger->println("available glfw extensions:");
    for (int i = 0; i < glfw_extension_count; i++) {
        std::cout << "\t" << glfw_extensions[i] << "\n";
    }
    logger->println("available extensions:");
    // loops through the extensions in the `extensions`
    // array and checks if the extensions are in the `glfw_extensions` array too
    for (const auto & extension : extensions) {
        if (std::find(glfw_extensions, glfw_extensions + glfw_extension_count, extension.extensionName) == glfw_extensions + glfw_extension_count)
//            std::cout << "\t" << extension.extensionName << " is not in the glfw_extensions array\n";
            std::cout << "\t!" << extension.extensionName << "\n";
        else
            std::cout << "\t" << extension.extensionName << "\n";
    }

    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS)
        logger->throw_err("vulkan instance creation error");
    else
        logger->println("vulkan instance created successfully");
}

void Engine::init_vulkan() {
    create_instance();
}

void Engine::loop() const {
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();
    }
}

void Engine::terminate() const {
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window.handle);
    glfwTerminate();
}