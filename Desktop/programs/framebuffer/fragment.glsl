#version 400 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float opacity = 1.f;

void main()
{
    FragColor = texture(screenTexture, TexCoords) * opacity;
}