#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <string>

int success;
char info_log[512];

void check_compile_status(GLuint shader, uint8_t type) {
    uint8_t _type_num = '\0';

    if (type == PROGRAM_TYPE) {
        glGetProgramInfoLog(shader, 512, NULL, info_log);
        _type_num = PROGRAM_TYPE;
    } else {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        _type_num = type ? VERTEX_TYPE : FRAGMENT_TYPE;
    }

    std::string _type_text;

    if (_type_num == 1)
        _type_text = "compiling vertex shader\n";
    else if (_type_num == 0)
        _type_text = "compiling fragment shader\n";
    else if (_type_num == 2)
        _type_text = "linking program shader\n";

    std::cout << "An error has occured while " << _type_text << info_log;
}

void shader_get_source(std::string path, std::string &source) {
    std::ifstream is {path};

    source = {std::istreambuf_iterator<char>(is), {}};
}

void shader_create(GLuint &shader, std::string &source,  uint8_t type) {
    if (type == VERTEX_TYPE)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *const _source = source.c_str();
    glShaderSource(shader, 1, &_source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
        check_compile_status(shader, type);
}

void shader_program_init(GLuint &program, GLuint vertex, GLuint fragment) {
    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
        check_compile_status(program, PROGRAM_TYPE);
}
