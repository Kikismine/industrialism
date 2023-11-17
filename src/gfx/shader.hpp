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
};

void shader_get_source(std::string path, std::string &source);
void shader_create(GLuint &shader, std::string &source,  uint8_t type);
void shader_program_init(GLuint &program, GLuint vertex, GLuint fragment);

#endif // SHADER_HPP
