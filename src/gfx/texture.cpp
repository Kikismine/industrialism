#define STB_IMAGE_IMPLEMENTATION

#include "texture.hpp"
#include <stb_image.h>

void texture_create2D(GLuint &handle, GLint wrap_m) {
    // gen texture
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    // set wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

    // set filtering params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void texture_load(GLint width, GLint height, GLint c_chan, std::string path) {
    // flip image
    /* stbi_set_flip_vertically_on_load(true); */

    // load texture
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &c_chan, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        LOG("An error has occured while loading texture");
    }

    stbi_image_free(data);
}
