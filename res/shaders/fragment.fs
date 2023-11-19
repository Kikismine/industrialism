#version 330 core
out vec4 frag_color;

in vec3 color;
in vec2 tex_coord;

uniform sampler2D wall;

void main() {
    frag_color = texture(wall, tex_coord);
}
