#version 330 core
out vec4 frag_color;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform sampler2D tex;

in vec3 Normal;
in vec3 FragPos;
in vec2 tex_coord;

void main() {

    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse ) * objectColor;

    // frag_color = texture(tex, tex_coord) * vec4(result, 1.0);
    frag_color = vec4(result, 1.0);

// vec3 texColor = texture(tex, tex_coord).rgb; // Sample the texture color
// vec3 result = (ambient + diffuse) * texColor; // Multiply lighting with texture
// frag_color = vec4(result, 1.0);

}
