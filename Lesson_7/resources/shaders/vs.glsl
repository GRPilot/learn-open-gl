#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 FragColor;
out vec2 TexCoord;

void main() {
    gl_Position = vec4(position, 1.0);
    FragColor = color;
    TexCoord = texCoord;
}
