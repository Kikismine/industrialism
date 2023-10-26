#include "vbo.hpp"
#include "../util/util.hpp"

void vbo_create(GLuint &vbo, GLfloat vertices[]) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
