#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main() {
	gl_Position = p * v * m * vec4(in_pos, 1.0);
	tex_coord = vec2(in_tex_coord.x, in_tex_coord.y);
}

