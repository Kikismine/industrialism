#include "vao.hpp"
#include "../util/util.hpp"

void vao_create(GLuint &vao) {
    glGenVertexArrays(1, &vao);
}

void vao_vertex_attrib() {
    // pos attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // texture coord attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void vao_bind(bool bind, GLuint vao) {
    if (bind)
        glBindVertexArray(vao);
    else
        glBindVertexArray(0);
}
