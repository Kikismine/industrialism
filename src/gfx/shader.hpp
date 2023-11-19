#ifndef SHADER_HPP
#define SHADER_HPP

#include "../util/util.hpp"

#define VERTEX_TYPE 1
#define FRAGMENT_TYPE 0
#define PROGRAM_TYPE 2

class Shader {
    public:
        GLuint shader;      // the main shader that will be stored
        uint8_t type;         // type of the shader
        std::string content;    // the shader code
        std::string path;   // path to the code

        void use() {
            glUseProgram(shader);
        }

        void shader_set_uniform_bool(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(shader, name.c_str()), (int) value);
        }

        void shader_set_uniform_int(const std::string &name, GLint value) const {
            glUniform1i(glGetUniformLocation(shader, name.c_str()), value);
        }

        void shader_set_uniform_float(const std::string &name, GLfloat value) const {
            glUniform1f(glGetUniformLocation(shader, name.c_str()), value);
        }
};

void shader_get_source(std::string path, std::string &source);
void shader_create(GLuint &shader, std::string &source,  uint8_t type);
void shader_program_init(GLuint &program, GLuint vertex, GLuint fragment);


#endif // SHADER_HPP
