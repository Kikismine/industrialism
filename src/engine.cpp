//
// Created by kikismine on 4/20/24.
//

#include <engine.hpp>
#include <initializers.hpp>
#include <images.hpp>
#include <complex>

void errorCallback(int error, const char* description) {
    std::cerr << "glfw error: " << description << "\n";
}

static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Engine::init() {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        throw std::runtime_error("failed to initialize glfw");
    else
        std::cout << "glfw initialized successfully\n";

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window.size = {1500, 800};
    window.title = "vulkan";

    window.handle = glfwCreateWindow((int) window.size.width, (int) window.size.height, window.title.c_str(), nullptr, nullptr);

    if (!window.handle) {
        glfwDestroyWindow(window.handle);
        glfwTerminate();
        throw std::runtime_error("failed to create glfw window");
    }
    std::cout << std::unitbuf << "glfw window created successfully";

    glfwSetKeyCallback(window.handle, keyboardCallback);

    init_vulkan();
    init_swapchain();
    init_commands();
    init_sync_structures();

    // everything is fine
    is_init = true;
}

void Engine::init_vulkan() {
    vkb::InstanceBuilder builder;

    // make the vulkan instance
    auto inst_ret = builder.set_app_name("Vulkan Engine")
            .request_validation_layers(r_validation_layers)
            .use_default_debug_messenger()
            .require_api_version(1, 3, 0)
            .build();

    vkb::Instance vkb_inst = inst_ret.value();

    instance = vkb_inst.instance;
    debug_messenger = vkb_inst.debug_messenger;

    // create the surface from the surface variable on the glfw window
    VkResult err = glfwCreateWindowSurface(instance, window.handle, nullptr, &surface);
    if (err) {
        terminate();
        throw std::runtime_error("failed to create a window surface");
    }

    // vulkan 1.3 features
    VkPhysicalDeviceVulkan13Features features{};
    features.dynamicRendering = true;
    features.synchronization2 = true;

    // vulkan 1.2 features
    VkPhysicalDeviceVulkan12Features features12{};
    features12.bufferDeviceAddress = true;
    features12.descriptorIndexing = true;

    // vkb selects the best GPU
    // filter gpu(s) based on `features` (vulkan 1.3) and `features12` (vulkan 1.2)
    vkb::PhysicalDeviceSelector selector{vkb_inst};
    vkb::PhysicalDevice vkb_physical_device = selector
            .set_minimum_version(1, 3)
            .set_required_features_13(features)
            .set_required_features_12(features12)
            .set_surface(surface)
            .select()
            .value();

    // create the vulkan (logical) device
    vkb::DeviceBuilder device_builder{vkb_physical_device};
    vkb::Device vkb_device = device_builder.build().value();

    // get the VkDevice handle from the `vkb_device`
    device = vkb_device.device;
    physical_device = vkb_physical_device.physical_device;

    // get graphics queue
    graphics_queue = vkb_device.get_queue(vkb::QueueType::graphics).value();
    graphics_queue_family = vkb_device.get_queue_index(vkb::QueueType::graphics).value();
}

void Engine::create_swapchain(std::uint32_t width, std::uint32_t height) {
    vkb::SwapchainBuilder builder{physical_device, device, surface};

    swapchain_image_format = VK_FORMAT_B8G8R8A8_UNORM;

    // set the swapchain builder params
    vkb::Swapchain vkb_swapchain = builder
//            .use_default_format_selection()
            .set_desired_format(VkSurfaceFormatKHR{.format = swapchain_image_format, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
                    // vsync
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(width, height)
            .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
            .build()
            .value();

    swapchain_extent = vkb_swapchain.extent;

    // store swapchain and its images (or vectors)
    swapchain = vkb_swapchain.swapchain;
    swapchain_images = vkb_swapchain.get_images().value();
    swapchain_image_views = vkb_swapchain.get_image_views().value();
}

void Engine::destroy_swapchain() {
    vkDestroySwapchainKHR(device, swapchain, nullptr);

    // destroy swapchain + its image(s)
    for (auto & swapchain_image_view : swapchain_image_views) {
        vkDestroyImageView(device, swapchain_image_view, nullptr);
    }
}

void Engine::init_swapchain() {
    create_swapchain(window.size.width, window.size.height);
}

void Engine::init_commands() {
    VkCommandPoolCreateInfo command_pool_info = init::command_pool_create_info(graphics_queue_family, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    for (int i = 0; i < FRAME_OVERLAP; ++i) {
        VK_CHECK(vkCreateCommandPool(device, &command_pool_info, nullptr, &frames[i].command_pool));

        // allocate the default command buffer
        VkCommandBufferAllocateInfo cmd_alloc_info = init::command_buffer_allocate_info(frames[i].command_pool, 1);

        VK_CHECK(vkAllocateCommandBuffers(device, &cmd_alloc_info, &frames[i].main_command_buffer));
    }
}

void Engine::init_sync_structures() {
    // create the sync structures
    VkFenceCreateInfo _fence_ci = init::fence_create_info(VK_FENCE_CREATE_SIGNALED_BIT);
    VkSemaphoreCreateInfo _semaphore_ci = init::semaphore_create_info();

    for (int i = 0; i < FRAME_OVERLAP; i++) {
        VK_CHECK(vkCreateFence(device, &_fence_ci, nullptr, &frames[i].render_fence));

        VK_CHECK(vkCreateSemaphore(device, &_semaphore_ci, nullptr, &frames[i].swapchain_semaphore));
        VK_CHECK(vkCreateSemaphore(device, &_semaphore_ci, nullptr, &frames[i].render_semaphore));
    }
}

void Engine::terminate() {
    if (is_init) {
        // check if gpu stopped doing things
        vkDeviceWaitIdle(device);

        // destroy command pools (frames..)
        for (int i = 0; i < FRAME_OVERLAP; ++i) {
            vkDestroyCommandPool(device, frames[i].command_pool, nullptr);

            // destroy sync objects
            vkDestroyFence(device, frames[i].render_fence, nullptr);
            vkDestroySemaphore(device, frames[i].swapchain_semaphore, nullptr);
            vkDestroySemaphore(device, frames[i].render_semaphore, nullptr);
        }

        destroy_swapchain();

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyDevice(device, nullptr);

        vkb::destroy_debug_utils_messenger(instance, debug_messenger);

        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window.handle);
        glfwTerminate();
    }
}

void Engine::draw() {
    // wait until the gpu has finished rendering the last frame, timeout 1s
    VK_CHECK(vkWaitForFences(device, 1, &get_current_frame().render_fence, true, 1000000000));
    VK_CHECK(vkResetFences(device, 1, &get_current_frame().render_fence));

    std::uint32_t swapchain_image_index;
    VK_CHECK(vkAcquireNextImageKHR(device, swapchain, 1000000000, get_current_frame().swapchain_semaphore, nullptr, &swapchain_image_index));

    // cmd = command_buffer
    VkCommandBuffer cmd = get_current_frame().main_command_buffer;

    // reset cb (commands are finished executing)
    VK_CHECK(vkResetCommandBuffer(cmd, 0));

    // begin the cb recording, using this cb just once => "one time submit bit"
    VkCommandBufferBeginInfo cb_begin_info = init::command_buffer_begin_info(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    // start the cb recording
    VK_CHECK(vkBeginCommandBuffer(cmd, &cb_begin_info));

    // make the swapchain image into writeable mode before rendering
    util::transition_image(cmd, swapchain_images[swapchain_image_index], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);

    // make a clear color from the frame number, 120 frame period flashing
    VkClearColorValue clear_value;
    float flash = std::abs(std::sin((float) frame_number / 120.f));
    clear_value = { {0.0f, 0.0f, flash, 1.0f} };

    VkImageSubresourceRange clear_range = init::image_subresource_range(VK_IMAGE_ASPECT_COLOR_BIT);

    // clear the image
    vkCmdClearColorImage(cmd, swapchain_images[swapchain_image_index], VK_IMAGE_LAYOUT_GENERAL, &clear_value, 1, &clear_range);

    // make the swapchain image into presentable mode
    util::transition_image(cmd, swapchain_images[swapchain_image_index], VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

    // finalize the cmd
    VK_CHECK(vkEndCommandBuffer(cmd));

    // prepare the submission to the queue

    VkCommandBufferSubmitInfo cmd_info = init::command_buffer_submit_info(cmd);

    VkSemaphoreSubmitInfo wait_info = init::semaphore_submit_info(VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR, get_current_frame().swapchain_semaphore);
    VkSemaphoreSubmitInfo signal_info = init::semaphore_submit_info(VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT, get_current_frame().render_semaphore);

    VkSubmitInfo2 submit = init::submit_info(&cmd_info, &signal_info, &wait_info);

    // submit cmd to the queue and execute it
    VK_CHECK(vkQueueSubmit2(graphics_queue, 1, &submit, get_current_frame().render_fence));

    // prepare present
    // this will put the final image to the window view

    VkPresentInfoKHR present_info = {};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.pNext = nullptr;
    present_info.pSwapchains = &swapchain;
    present_info.swapchainCount = 1;

    present_info.pWaitSemaphores = &get_current_frame().render_semaphore;
    present_info.waitSemaphoreCount = 1;

    present_info.pImageIndices = &swapchain_image_index;

    VK_CHECK(vkQueuePresentKHR(graphics_queue, &present_info));

    // increase the number of frames drawn
    frame_number++;
}

void Engine::run() {
    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();
        draw();
    }
}