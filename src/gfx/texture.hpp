#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../util/util.hpp"

class Texture {
    public:
        GLuint handle;
        int width, height;
        std::string path;
        GLint c_chan; // number of color channels for stb_image
};

void texture_create2D(GLuint &handle, GLint wrap_m);
void texture_load(GLint width, GLint height, GLint c_chan, std::string path, bool flip);

#endif /* ifndef TEXTURE_HPP */
