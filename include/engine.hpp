#pragma once

#include <util.hpp>
#include <logger.hpp>
#include <renderer.hpp>
#include <window.hpp>

class Window;

class Engine {
public:
    std::unique_ptr<Window> window = std::make_unique<Window>(1500, 900, "industrialism");

    void run();
    void loop();
    void terminate();
};