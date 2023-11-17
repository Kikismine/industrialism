#ifndef SHADER_HPP
#define SHADER_HPP

#include "../util/util.hpp"

#define VERTEX_TYPE 1
#define FRAGMENT_TYPE 0
#define PROGRAM_TYPE 2

class Shader {
    public:
        GLuint shader;
        GLint type;
        GLchar *content;
        std::string path;
};

void check_max_vertex_attribs();
void get_shader_source(std::string path, GLchar *&shaderFile);
void create_shader(GLuint &shader, GLint type, GLchar *source);
void create_shader_program(GLuint &shader_program, GLint type, unsigned int vertex_shader, unsigned int fragment_shader);
void compile_shader(GLuint shader, GLint type);
void check_compile_status(GLuint shader, GLint type, GLuint program);
void delete_shader(GLuint shader);

#endif // SHADER_HPP
