#include <logger.hpp>

Logger *Logger::logger;

void Logger::set_mode(bool mode) {
    enabled = mode;
}

bool Logger::is_enabled() {
    return enabled;
}

Logger *Logger::get_logger() {
    if (!logger)
        logger = new Logger();

    return logger;
}

void Logger::print(std::string message) {
    if (!enabled) return;

    std::cout << message << "\n";
}

void Logger::println(std::string message) {
    if (!enabled) return;

    std::cout << message << std::endl;
}

void Logger::throw_err(std::string message) {
    if (!enabled) return;

    throw std::runtime_error(message);
}
