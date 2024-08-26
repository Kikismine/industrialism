#pragma once

#include <util.hpp>
#include <logger.hpp>
#include <renderer.hpp>
#include <window.hpp>

class Window;

class Engine {
public:
    std::unique_ptr<Window> window = std::make_unique<Window>(1500, 900, "industrialism");

    Renderer* renderer = Renderer::get_renderer();
    Logger* logger = Logger::get_logger();

    void run();
    void loop();
    void terminate();

    void init_input();

    void quit();
    void red_higher();
    void red_lower();
};