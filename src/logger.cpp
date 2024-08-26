#include <logger.hpp>

Logger *Logger::logger;

Logger *Logger::get_logger() {
    if (!logger)
        logger = new Logger();

    return logger;
}

void Logger::print(std::string message) {
    std::cout << message << "\n";
}

void Logger::println(std::string message) {
    std::cout << message << std::endl;
}

void Logger::throw_err(std::string message) {
    throw std::runtime_error(message);
}