#version 400 core

out vec4 FragColor;

in VS_OUT {
    vec2 texture;
    vec3 normal;
    vec3 location;
} vs_in;

void main() {
    FragColor = vec4(1.f);
}