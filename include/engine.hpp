#pragma once

#include <util.hpp>
#include <logger.hpp>

struct Window {
    GLFWwindow *handle;
    const VkExtent2D size {1500, 800};
    std::string title {"vulkan"};
};

class Engine {
public:
    Window window;
    Logger *logger = Logger::get_logger();

    // vulkan variables
    VkInstance instance;

    void run() {
        logger->set_mode(true);

        init_window();
        init_vulkan();
        loop();
        terminate();
    }
private:
    void init_window();
    void init_vulkan();
    void create_instance();
    void loop() const;
    void terminate() const;
};