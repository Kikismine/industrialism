#pragma once

#include <util.hpp>

class Logger {
public:
    static Logger *logger;

    static Logger *get_logger();
    void set_mode(bool mode);
    bool is_enabled();
    void print(std::string message);
    void println(std::string message);
    void throw_err(std::string message);
private:
    bool enabled;
};
