#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D grass_top;

void main() {
    frag_color = texture(grass_top, tex_coord);
}
