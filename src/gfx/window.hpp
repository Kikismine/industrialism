#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../util/util.hpp"
#include "unistd.h"

class Window {
    public:
        GLFWwindow* handle;

        std::vector<std::uint16_t> size{800, 600};
        std::string title{"window"};

        bool is_apple = _is_apple();

        void create_window();
        void init_glfw(GLuint major, GLuint minor);

    private:
        bool ap_debug = false;

        bool _is_apple() {
            if (sysconf(_SC_VERSION)) {
                if (ap_debug == true)
                    std::cout << "sc on" << std::endl;
                return true;
            } else {
                if (ap_debug == true)
                    std::cout << "sc off" << std::endl;
                return false;
            }
        }
};

#endif /* ifndef WINDOW_HPP */
