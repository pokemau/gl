#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex_coord;
layout(location = 2) in vec3 in_normal;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out vec2 tex_coord;
out vec3 FragPos;
out vec3 Normal;

void main() {
    FragPos = vec3(m * vec4(in_pos, 1.0));
    Normal = mat3(transpose(inverse(m))) * in_normal;

    tex_coord = vec2(in_tex_coord.x, in_tex_coord.y);

    gl_Position = p * v * m * vec4(in_pos, 1.0);
}
