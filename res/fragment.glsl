#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;

void main()
{
//	FragColor = vec4(ourColor, 1.0f);
	FragColor = texture(texture1, texCoord);
//	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
