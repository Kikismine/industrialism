#include "shader.hpp"
#include <fstream>
#include <string>

static int success;
static char infoLog[512];
static GLint nrAttribs;

char *convert(std::string str)
{
    size_t len = str.length();
    char *buf = new char[len + 1];
    memcpy(buf, str.data(), len);
    buf[len] = '\0';
    return buf;
}

void get_shader_source(std::string path, GLchar *&shader_file)
{
    std::ifstream is {path};
    std::string line, text;

    if (is.good()) {
        while (std::getline(is, line)) {
            text += line + "\n";
        }
    } else {
        LOG_ERR("An error has occured while reading shader files");
        exit(-1);
    }

    shader_file = convert(text);

    is.close();
}

void check_max_vertex_attribs()
{
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttribs);
    std::cout << "Maximum number of vertex attribues supported: " << nrAttribs << std::endl;
}

void create_shader(GLuint &shader, GLint type, GLchar *source)
{
    shader = glCreateShader(type ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &source, NULL);
}

void create_shader_program(GLuint &shader_program, GLint type, unsigned int vertex_shader, unsigned int fragment_shader)
{
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    check_compile_status(shader_program, type, 1);
}

void compile_shader(GLuint shader, GLint type)
{
    glCompileShader(shader);
    check_compile_status(shader, type, 0);
}

void delete_shader(GLuint shader)
{
    glDeleteShader(shader);
}

void check_compile_status(GLuint shader, GLint type, GLuint program)
{
    std::string text;

    glGetProgramiv(shader, program ? GL_LINK_STATUS : GL_COMPILE_STATUS, &success);

    if (!success)
    {
        if (program)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            if (strlen(infoLog) == 0)
                return;
            LOG_ERR("An error has occured while linking program shader");
        }
        else
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            if (strlen(infoLog) == 0)
                return;

            text = type ? "vertex" : "fragment";

            std::cerr
                << "An error has occured while compiling " << text << " shader" << std::endl;
            std::cerr << infoLog << std::endl;
        }
    }
}
