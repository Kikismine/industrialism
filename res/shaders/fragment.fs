#version 330 core
out vec4 frag_color;

in vec3 color;
in vec2 tex_coord;

uniform sampler2D wall;
uniform sampler2D spider;
uniform bool rgb;
uniform bool cvr;

void main() {
    if (cvr == true) {
        if (rgb == true)
            frag_color = mix(texture(wall, tex_coord), texture(spider, tex_coord), 0.3) * vec4(color, 1.0);
        else
            frag_color = mix(texture(wall, tex_coord), texture(spider, tex_coord), 0.3);
    } else {
        if (rgb == true)
            frag_color = texture(wall, tex_coord) * vec4(color, 1.0);
        else
            frag_color = texture(wall, tex_coord);
    }
}
