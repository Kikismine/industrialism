#include "vbo.hpp"
#include "../util/util.hpp"

void vbo_create(GLuint &vbo, GLfloat vertices[]) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices_size = sizeof(vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
}

void vbo_create(GLuint &handle) {
    glGenBuffers(1, &handle);
}

void vbo_buffer(GLuint handle, float vertices[], GLsizei size) {
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
