#version 400 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 TexCoords;

void main() {
    gl_Position = vec4(-1.f, -1.f, 0.f, 1.f);
    TexCoords = vec2(0.f, 0.f);
    EmitVertex();
    gl_Position = vec4(-1.f, 1.f, 0.f, 1.f);
    TexCoords = vec2(0.f, 1.f);
    EmitVertex();
    gl_Position = vec4(1.f, -1.f, 0.f, 1.f);
    TexCoords = vec2(1.f, 0.f);
    EmitVertex();
    gl_Position = vec4(1.f, 1.f, 0.f, 1.f);
    TexCoords = vec2(1.f, 1.f);
    EmitVertex();
    EndPrimitive();
}