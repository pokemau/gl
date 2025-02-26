#version 330 core

out vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D tex;

void main() {
	frag_color = texture(tex, tex_coord);
//	frag_color = vec4(0.0f,0.5f,0.2f, 1.0f);
}
