#version 330 core
in vec4 FragmentColor;
in vec2 TexturePosition;

out vec4 ResultColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform bool useColor = true;
uniform bool useTexture = true;
uniform bool hflip = false;
uniform bool vflip = false;
uniform float inter_value = 0.5;

void main() {
    vec4 textures = vec4(0, 0, 0, 1.0);
    if(useTexture) {
        vec2 texPos = TexturePosition;
        if(hflip) {
            texPos.x = 1.0 - texPos.x;
        }
        if(vflip) {
            texPos.y = 1.0 - texPos.y;
        }
        textures = mix(texture(texture0, texPos), texture(texture1, texPos), inter_value);
    }

    vec4 clr = vec4(0, 0, 0, 1.0);
    if(useColor) {
        clr = FragmentColor;
    }
    ResultColor = clr + textures;
}

