#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texture_position;

out vec4 FragmentColor;
out vec2 TexturePosition;

void main() {
    gl_Position = vec4(position, 1.0f);
    FragmentColor = color;
    TexturePosition = texture_position;
}