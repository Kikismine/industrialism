#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex_coord;

out vec2 tex_coord;

uniform mat4 projection; // projection uniform
uniform mat4 view; // view uniform
uniform mat4 model; // model uniform

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0f);
    tex_coord = v_tex_coord;
}
