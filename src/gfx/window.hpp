#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../util/util.hpp"

class Window {
    public:
        GLFWwindow* handle;

        std::vector<std::uint16_t> size{1000, 800};
        std::string title{"window"};

        bool is_apple = _is_apple(); 

        void create_window();
        void init_glfw(GLuint major, GLuint minor);

    private:
        bool _is_apple() {
            if (__APPLE__)
                return true;
            else
                return false;
        }
};

#endif /* ifndef WINDOW_HPP */
