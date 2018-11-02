#version 400 core

layout(location = 0) in vec3 location;
layout(location = 1) in vec2 texture;
layout(location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT
{
    vec2 texture;
    vec3 normal;
    vec3 location;
} vs_out;

void main() {
    mat4 transform = projection * view * model;

    gl_Position = transform * vec4(location, 1.f);

    vs_out.texture = texture;
    vs_out.normal = (model * vec4(normal, 1.f)).xyz;
    vs_out.location = (model * vec4(location, 1.f)).xyz;
}