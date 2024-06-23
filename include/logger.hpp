#pragma once

#include <util.hpp>

class Logger {
public:
    void print(std::string message);
    void println(std::string message);
    void throw_err(std::string message);
};
