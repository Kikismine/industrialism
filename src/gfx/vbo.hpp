#ifndef VBO_HPP
#define VBO_HPP value

#include "../util/util.hpp"

class VBO {
    public:
    GLuint handle;
};

void vbo_create(GLuint &handle);
void vbo_buffer(GLuint handle, float vertices[], GLsizei size);
void vbo_unbind();

#endif /* ifndef VBO_HPP */
