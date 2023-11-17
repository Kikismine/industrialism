#ifndef VAO_HPP
#define VAO_HPP value

#include "../util/util.hpp"

class VAO {
    public:
    GLuint handle;
};

void vao_create(GLuint &handle);
void vao_vertex_attrib();
void vao_bind(bool bind, GLuint vao);

#endif /* ifndef VAO_HPP */
