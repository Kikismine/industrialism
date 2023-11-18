#include "vbo.hpp"
#include "../util/util.hpp"
#include <span>

void vbo_create(GLuint &vbo, std::span<GLfloat> vertices) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);
}

void vbo_create(GLuint &handle) {
    glGenBuffers(1, &handle);
}
void vbo_buffer(GLuint handle, float vertices[], GLsizei v_size) {
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
}

void ebo_buffer(GLuint handle, GLuint indices[], GLsizei i_size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);
}

void vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
